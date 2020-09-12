//
//  helper.cpp
//  FP
//
//  Created by Yuhua Cai on 2019/12/1.
//  Copyright © 2019 Yuhua Cai. All rights reserved.
//

#include "helper.hpp"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include <list>
#include <map>
#include <sstream>
#include <stack>
#include <string>

#include "expr.hpp"
#include "functions.hpp"
#include "step3.hpp"

using namespace std;

//Equal Condition
bool equals(std::string & lhs, std::string & rhs) {
  double dlhs = stod(lhs);
  double drhs = stod(rhs);
  return fabs(dlhs - drhs) < 0.0000000000001;
}

//parse values
std::list<std::string> values(string s) {
  std::list<string> values;
  string s1half;
  std::size_t fl = s.find_last_of(")");
  std::size_t ff = s.find_first_of("(");
  if (fl != (size_t)-1 && ff != (size_t)-1) {
    s1half = s.substr(ff + 1, fl - ff - 1);
  }

  const size_t len = s1half.length();

  char * cstr = new char[len + 1];
  strcpy(cstr, s1half.c_str());
  char * p = strtok(cstr, " ");
  while (p != 0) {
    std::string ss(p);
    values.push_front(ss);
    p = strtok(NULL, " ");
  }
  delete[] cstr;
  return values;
}

//parse variables
std::list<std::string> variable(const char ** strp) {
  std::list<std::string> variables;
  std::string s(*strp);
  std::size_t eq = s.find("=");
  std::string s1half = s.substr(0, eq);

  std::size_t fl1 = s1half.find_last_of(")");
  std::size_t ff1 = s1half.find_first_of("(");
  if (fl1 != (size_t)-1 && ff1 != (size_t)-1) {
    s = s.substr(ff1 + 1, fl1 - ff1 - 1);
  }

  const size_t len = s.length();
  char * cstr = new char[len + 1]();
  strcpy(cstr, s.c_str());
  char * p = strtok(cstr, " ");
  while (p != NULL) {
    std::string ss(p);
    variables.push_front(ss);
    p = strtok(NULL, " ");
  }
  delete[] cstr;

  return variables;
}

//function invoked by finalExpr for substitution
string exPredefine(string final, string prefname, string subs) {
  size_t pos = final.find(prefname);
  size_t len = prefname.length();
  while (pos != (size_t)-1) {
    final.replace(pos, len, subs);
    pos = final.find(prefname);
  }
  return final;
}

//Check build-in functions and substitude using special charactors
string finalExpr(string final) {
  string ans;
  ans = exPredefine(final, "floor", "!");
  ans = exPredefine(ans, "ceil", "?");
  ans = exPredefine(ans, "round", "@");
  ans = exPredefine(ans, "logb", "#");
  return ans;
}

//Function for dealing with the complicated function definition
string complicatedDef(string complicatedExpr, list<Function> funcList) {
  stack<int> mystack;

  for (int i = 0; (size_t)i < complicatedExpr.length(); i++) {
    if (complicatedExpr[i] == '(') {
      mystack.push(i);
    }
    if (complicatedExpr[i] == ')') {
      int j = mystack.top();
      mystack.pop();
      string sub = complicatedExpr.substr(j, i - j + 1);
      string result = to_string(calculate(sub, funcList));
      size_t len1 = sub.length();
      complicatedExpr.replace(j, len1, result);
      i = j;
    }
  }
  return complicatedExpr;
}

//Function for getting final expression and calculating its value by evaluate()
double calculate(string expr, list<Function> funcList) {
  std::list<std::string> val;
  double result = 0;
  val = values(expr);

  list<Function>::iterator iter;
  iter = funcList.begin();

  while (iter != funcList.end()) {
    if (iter->fname == val.back()) {
      std::map<std::string, string> mymap;

      auto it = iter->variables.begin();

      while (it != iter->variables.end()) {
        string value = val.front();
        val.pop_front();
        mymap.insert(std::pair<std::string, string>(*it, value));
        ++it;
      }
      string final = iter->expr;
      //Map used for substitude variables by values
      map<std::string, string>::iterator iter1;
      iter1 = mymap.begin();
      while (iter1 != mymap.end()) {
        size_t pos = final.find(iter1->first);
        size_t len = iter1->first.length();
        while (pos != (size_t)-1) {
          final.replace(pos, len, iter1->second);
          pos = final.find(iter1->first);
        }
        iter1++;
      }

      final = complicatedDef(final, funcList);

      const char * numexpr = final.c_str();

      Expression * num = parse(&numexpr);
      result = num->evaluate();
      delete num;
      return result;
    }
    iter++;
  }

  if (expr.find_first_of("+-/%*^!?@#") != (size_t)-1) {
    const char * numExpr = expr.c_str();
    Expression * expression = parse(&numExpr);
    result = expression->evaluate();
    delete expression;
  }

  return result;
}

//find function from list<Function>
Function findFunction(string s, list<Function> funcs) {
  list<string> argNumint = parseNumint(s);
  list<Function>::iterator iter;
  iter = funcs.begin();
  while (iter != funcs.end()) {
    if (iter->fname == argNumint.back()) {
      return *iter;
    }
    iter++;
  }
  abort();
  return *funcs.begin();
}
