//
//  step2.cpp
//  FP
//
//  Created by Yuhua Cai on 2019/12/5.
//  Copyright © 2019 Yuhua Cai. All rights reserved.
//

#include "step2.hpp"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>

#include "expr.hpp"
#include "functions.hpp"
#include "helper.hpp"
#include "step3.hpp"

//make new Expression for recursion
string makeNewExpr(Function original, double num, bool multi) {
  string arg = *original.variables.begin();
  string number = to_string(num);
  string originalExpr = original.expr;
  if (size_t i = original.expr.find("\n")) {
    originalExpr = originalExpr.substr(0, i);
  }
  size_t pos = originalExpr.find(arg);
  size_t len = arg.length();
  while (pos != (size_t)-1) {
    originalExpr.replace(pos, len, number);
    pos = originalExpr.find(arg);
  }
  //According to the formula, the functional value needs
  //calculating twice except for the start and end point
  if (multi) {
    originalExpr = "(* 2 " + originalExpr + " ) ";
    return originalExpr;
  }
  return originalExpr;
}

//mergeAll for buliding the final Equation
string mergeAll(list<string> exprSet, string step) {
  std::stringstream answer;
  list<string>::iterator it = exprSet.begin();
  string addTwo = "(+ " + *it;
  it++;
  addTwo = addTwo + " " + *it + ")";
  it++;
  while (it != exprSet.end()) {
    addTwo = "(+ " + addTwo + " " + *it + ")";
    it++;
  }
  addTwo = "(* (/ " + addTwo + " 2) " + step + ")";
  return addTwo;
}

//recursive method to each variable
double recursiveCall(vector<vector<double> > pointBetween,
                     Function found,
                     string stepSize) {
  Function newExpr = found;
  newExpr.variables.reverse();
  vector<vector<double> >::iterator start;
  start = pointBetween.begin();
  while (start != pointBetween.end()) {
    //list of expression waiting for merge
    list<string> exprSet;
    vector<double>::iterator it = start->begin();
    while (it != start->end()) {
      if (it == start->begin() || it == start->end() - 1) {
        exprSet.push_back(makeNewExpr(newExpr, *it, false));
      }
      else {
        exprSet.push_back(makeNewExpr(newExpr, *it, true));
      }
      it++;
    }

    newExpr.expr = mergeAll(exprSet, stepSize);

    newExpr.variables.pop_front();

    start++;
  }
  const char * numexpr = newExpr.expr.c_str();
  Expression * num = parse(&numexpr);
  double result = num->evaluate();
  delete num;
  return result;
}

//vector<double> for each variable to store every point based on range and stepsize
vector<vector<double> > pointList(string s, list<Function> funcs) {
  vector<vector<double> > pointBetween;
  list<string> argNumint = parseNumint(s);
  list<Function>::iterator iter;
  iter = funcs.begin();
  while (iter != funcs.end()) {
    if (iter->fname == argNumint.back()) {
      //error dealing
      if (iter->variables.size() != ((argNumint.size() / 2) - 1)) {
        cerr << "Wrong number of arguments\n";
        break;
      }
      string fname = argNumint.back();
      argNumint.pop_back();
      double stepSize = stod(argNumint.back());
      argNumint.pop_back();

      list<string>::iterator iter1;
      iter1 = argNumint.begin();
      list<pair<double, double> > getPair;
      while (!argNumint.empty()) {
        double lhs = stod(argNumint.front());
        iter1++;
        argNumint.pop_front();
        double rhs = stod(argNumint.front());
        iter1++;
        argNumint.pop_front();
        getPair.push_front(pair<double, double>(lhs, rhs));
      }

      list<pair<double, double> >::iterator iter2;
      iter2 = getPair.begin();

      while (iter2 != getPair.end()) {
        vector<double> points;
        double lhs = iter2->second;
        double rhs = iter2->first;
        while (lhs <= rhs) {
          points.push_back(lhs);
          lhs = lhs + stepSize;
        }
        pointBetween.push_back(points);
        iter2++;
      }
    }
    iter++;
  }
  return pointBetween;
}
