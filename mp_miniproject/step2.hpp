//
//  step2.hpp
//  FP
//
//  Created by Yuhua Cai on 2019/12/5.
//  Copyright © 2019 Yuhua Cai. All rights reserved.
//

#ifndef step2_hpp
#define step2_hpp

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>

#include "functions.hpp"

using namespace std;

string makeNewExpr(Function original, double num, bool multi);
string mergeAll(list<string> exprSet, string step);
double recursiveCall(vector<vector<double> > pointBetween,
                     Function found,
                     string stepSize);
vector<vector<double> > pointList(string s, list<Function> funcs);

#endif /* step2_hpp */
