//
//  helper.hpp
//  FP
//
//  Created by Yuhua Cai on 2019/12/1.
//  Copyright © 2019 Yuhua Cai. All rights reserved.
//

#ifndef helper_hpp
#define helper_hpp

#include <math.h>
#include <stdio.h>
#include <string.h>

#include <list>
#include <sstream>
#include <string>

#include "functions.hpp"

using namespace std;

bool equals(std::string & lhs, std::string & rhs);
std::list<std::string> values(string s);
std::list<std::string> variable(const char ** strp);
double calculate(string expr, list<Function> funcList);
string exPredefine(string final, string prefname, string subs);
string finalExpr(string final);
string complicatedDef(string complicatedExpr, list<Function> funcList);
Function findFunction(string s, list<Function> funcs);

#endif /* helper_hpp */
