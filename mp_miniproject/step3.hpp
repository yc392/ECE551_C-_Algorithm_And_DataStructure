//
//  step3.hpp
//  FP
//
//  Created by Yuhua Cai on 2019/11/29.
//  Copyright © 2019 Yuhua Cai. All rights reserved.
//

#ifndef step3_hpp
#define step3_hpp

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <list>

#include "functions.hpp"
using namespace std;

double calculateMcint(string s, list<Function> funcs);
list<string> parseNumint(string s);
list<double> getDiff(list<pair<double, double> > getPair);

#endif /* step3_hpp */
