//
//  step3.cpp
//  FP
//
//  Created by Yuhua Cai on 2019/11/29.
//  Copyright © 2019 Yuhua Cai. All rights reserved.
//

#include "step3.hpp"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <list>
#include <random>
#include <vector>

#include "expr.hpp"
#include "functions.hpp"
#include "helper.hpp"

using namespace std;

//function for Monte Carlo Integration
double calculateMcint(string s, list<Function> funcs) {
  double result = 0;
  list<Function>::iterator iter;
  list<string> argMcint = parseNumint(s);
  iter = funcs.begin();
  while (iter != funcs.end()) {
    if (iter->fname == argMcint.back()) {
      if (iter->variables.size() != ((argMcint.size() / 2) - 1)) {
        cerr << "Wrong number of arguments\n";
        break;
      }
      string fname = argMcint.back();
      argMcint.pop_back();

      int trials = stoi(argMcint.back());
      argMcint.pop_back();

      list<string>::iterator iter1;
      iter1 = argMcint.begin();
      list<pair<double, double> > getPair;
      while (!argMcint.empty()) {
        double lhs = stod(argMcint.front());

        iter1++;
        argMcint.pop_front();
        double rhs = stod(argMcint.front());

        iter1++;
        argMcint.pop_front();
        getPair.push_front(pair<double, double>(lhs, rhs));
      }

      size_t varSize = iter->variables.size();
      list<pair<double, double> >::iterator iter2;

      list<double> difference = getDiff(getPair);

      iter2 = getPair.begin();
      vector<vector<double> > num;
      while (iter2 != getPair.end()) {
        vector<double> subnum;
        //Cite from C++ reference to generate random values
        random_device generator;
        uniform_real_distribution<double> distribution(iter2->first, iter2->second);
        for (int j = 0; j < trials; j++) {
          subnum.push_back(distribution(generator));
        }
        num.push_back(subnum);

        iter2++;
      }

      for (int i = 0; i < trials; i++) {
        std::stringstream answer;
        answer << "(" << fname;
        for (size_t j = 0; j < varSize; j++) {
          answer << " " << num[j][i];
        }
        answer << ")" << endl;
        double res = calculate(answer.str(), funcs);

        result += res;
      }

      list<double>::iterator it;
      it = difference.begin();
      while (it != difference.end()) {
        result = result * (*it);

        it++;
      }
      result = result / trials;
      break;
    }

    iter++;
  }

  return result;
}

//parse line for arguments
list<string> parseNumint(string s) {
  list<string> argNumint;
  const size_t len = s.length();
  char * cstr = new char[len + 1];
  strcpy(cstr, s.c_str());
  char * pch = strtok(cstr, " ");
  while (pch != 0) {
    std::string ss(pch);
    argNumint.push_front(ss);
    pch = strtok(NULL, " ");
  }
  argNumint.pop_back();
  delete[] cstr;
  return argNumint;
}

//get differences between ranges
list<double> getDiff(list<pair<double, double> > getPair) {
  list<double> diff;
  list<pair<double, double> >::iterator it;
  it = getPair.begin();
  while (it != getPair.end()) {
    diff.push_back(it->first - it->second);
    it++;
  }
  return diff;
}
