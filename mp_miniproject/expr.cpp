//
//  expr.cpp
//  FP
//
//  Created by Yuhua Cai on 2019/12/1.
//  Copyright © 2019 Yuhua Cai. All rights reserved.
//

#include "expr.hpp"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>

// This file Cite from Assignment 83~85

void skipSpace(const char ** strp) {
  while (isspace(**strp)) {
    *strp = *strp + 1;
  }
}

// % , ^, floor, ceil, round, logb, select added to makeExpr
Expression * makeExpr(char op, Expression * lhs, Expression * rhs) {
  switch (op) {
    case '+':
      return new PlusExpression(lhs, rhs);
    case '-':
      return new MinusExpression(lhs, rhs);
    case '*':
      return new TimesExpression(lhs, rhs);
    case '/':
      return new DivExpression(lhs, rhs);
    case '%':
      return new LdivExpression(lhs, rhs);
    case '^':
      return new PowExpression(lhs, rhs);
    case '!':
      return new floorExpression(lhs);
    case '?':
      return new ceilExpression(lhs);
    case '@':
      return new roundExpression(lhs);
    case '#':
      return new logbExpression(lhs, rhs);
    default:
      std::cerr << "Impossible op char: " << op << "\n";
      abort();
  }
}

bool isValidOp(char c) {
  return strchr("+-*/%^!?@#", c) != NULL;
}

Expression * parseOp(const char ** strp) {
  skipSpace(strp);
  char op = **strp;
  if (!isValidOp(op)) {
    std::cerr << "Invalid op: " << op << "\n";
    return NULL;
  }
  *strp = *strp + 1;
  Expression * lhs = parse(strp);
  Expression * rhs = parse(strp);

  skipSpace(strp);
  if (**strp == ')') {
    *strp = *strp + 1;
    return makeExpr(op, lhs, rhs);
  }
  std::cerr << "Expected ) but found " << *strp << "\n";
  delete lhs;
  delete rhs;
  return NULL;
}

Expression * parse(const char ** strp) {
  skipSpace(strp);
  if (**strp == '\0') {
    std::cerr << "End of line found mid expression!\n";
    return NULL;
  }
  else if (**strp == '(') {
    // (op E E)
    *strp = *strp + 1;
    return parseOp(strp);
  }
  else if (**strp == ')') {
    return NULL;
  }
  else {
    //number
    std::string c;
    std::string s(*strp);
    std::size_t space = s.find_first_of(" )");
    c = s.substr(0, space);
    *strp = *strp + c.length();

    return new NumExpression(c);
  }
}
