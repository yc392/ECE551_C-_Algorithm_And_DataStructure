//
//  expr.hpp
//  FP
//
//  Created by Yuhua Cai on 2019/12/1.
//  Copyright © 2019 Yuhua Cai. All rights reserved.
//

#ifndef expr_hpp
#define expr_hpp

#include <math.h>
#include <stdio.h>
#include <string.h>

#include <sstream>
#include <string>

// Class Expression Cite from Assignment 83~85
// % , ^, floor, ceil, round, logb, select added as requirement
// All of these are dealt with by Expressions

class Expression {
 public:
  Expression() {}
  virtual std::string toString() const = 0;
  virtual double evaluate() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
  std::string number;

 public:
  NumExpression(std::string n) : number(n) {}
  virtual std::string toString() const { return number; }
  virtual double evaluate() const {
    double ans = stod(number);
    return ans;
  }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
  Expression * l;
  Expression * r;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual std::string toString() const {
    std::stringstream answer;
    answer << "(" << l->toString() << " + " << r->toString() << ")";
    return answer.str();
  }
  virtual double evaluate() const {
    double ans;
    ans = l->evaluate() + r->evaluate();
    return ans;
  }
  virtual ~PlusExpression() {
    delete l;
    delete r;
  }
};

class MinusExpression : public Expression {
  Expression * l;
  Expression * r;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual std::string toString() const {
    std::stringstream answer;
    answer << "(" << l->toString() << " - " << r->toString() << ")";
    return answer.str();
  }
  virtual double evaluate() const {
    double ans;
    ans = l->evaluate() - r->evaluate();
    return ans;
  }
  virtual ~MinusExpression() {
    delete l;
    delete r;
  }
};

class TimesExpression : public Expression {
  Expression * l;
  Expression * r;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual std::string toString() const {
    std::stringstream answer;
    answer << "(" << l->toString() << " * " << r->toString() << ")";
    return answer.str();
  }
  virtual double evaluate() const {
    double ans;
    ans = l->evaluate() * r->evaluate();
    return ans;
  }
  virtual ~TimesExpression() {
    delete l;
    delete r;
  }
};

class DivExpression : public Expression {
  Expression * l;
  Expression * r;

 public:
  DivExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual std::string toString() const {
    std::stringstream answer;
    answer << "(" << l->toString() << " / " << r->toString() << ")";
    return answer.str();
  }
  virtual double evaluate() const {
    double ans;
    ans = l->evaluate() / r->evaluate();
    return ans;
  }
  virtual ~DivExpression() {
    delete l;
    delete r;
  }
};

class PowExpression : public Expression {
  Expression * l;
  Expression * r;

 public:
  PowExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual std::string toString() const {
    std::stringstream answer;
    answer << "(" << l->toString() << " ^ " << r->toString() << ")";
    return answer.str();
  }
  virtual double evaluate() const {
    double ans;
    ans = pow(l->evaluate(), r->evaluate());
    return ans;
  }
  virtual ~PowExpression() {
    delete l;
    delete r;
  }
};

class LdivExpression : public Expression {
  Expression * l;
  Expression * r;

 public:
  LdivExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual std::string toString() const {
    std::stringstream answer;
    answer << "(" << l->toString() << " % " << r->toString() << ")";
    return answer.str();
  }
  virtual double evaluate() const {
    double ans;
    ans = fmod(l->evaluate(), r->evaluate());
    return ans;
  }
  virtual ~LdivExpression() {
    delete l;
    delete r;
  }
};

class floorExpression : public Expression {
  Expression * arg;

 public:
  floorExpression(Expression * num) : arg(num) {}
  virtual std::string toString() const {
    std::stringstream answer;
    answer << "(" << arg->toString() << ")";
    return answer.str();
  }
  virtual double evaluate() const { return floor(arg->evaluate()); }
  virtual ~floorExpression() { delete arg; }
};

class ceilExpression : public Expression {
  Expression * arg;

 public:
  ceilExpression(Expression * num) : arg(num) {}
  virtual std::string toString() const {
    std::stringstream answer;
    answer << "(" << arg->toString() << ")";
    return answer.str();
  }
  virtual double evaluate() const { return ceil(arg->evaluate()); }
  virtual ~ceilExpression() { delete arg; }
};

class roundExpression : public Expression {
  Expression * arg;

 public:
  roundExpression(Expression * num) : arg(num) {}
  virtual std::string toString() const {
    std::stringstream answer;
    answer << "(" << arg->toString() << ")";
    return answer.str();
  }
  virtual double evaluate() const { return round(arg->evaluate()); }
  virtual ~roundExpression() { delete arg; }
};

class logbExpression : public Expression {
  Expression * l;
  Expression * r;

 public:
  logbExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual std::string toString() const {
    std::stringstream answer;
    answer << "(" << l->toString() << " % " << r->toString() << ")";
    return answer.str();
  }
  virtual double evaluate() const { return log(l->evaluate()) / log(r->evaluate()); }
  virtual ~logbExpression() {
    delete l;
    delete r;
  }
};

Expression * parse(const char ** strp);
void skipSpace(const char ** strp);
Expression * makeExpr(char op, Expression * lhs, Expression * rhs);
bool isValidOp(char c);
Expression * parseOp(const char ** strp);

#endif /* expr_hpp */
