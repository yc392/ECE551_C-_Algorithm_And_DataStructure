//
//  functions.hpp
//  FP
//
//  Created by Yuhua Cai on 2019/11/23.
//  Copyright © 2019 Yuhua Cai. All rights reserved.
//

#ifndef functions_hpp
#define functions_hpp

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <list>
#include <sstream>
#include <string>

using namespace std;

//Class for Function
class Function {
 public:
  //Three fields
  string fname;
  std::list<string> variables;
  string expr;

  //Constructor
  Function(string initFname, list<string> initVar, string initExpr) :
      fname(initFname),
      variables(initVar),
      expr(initExpr) {}

  //Destructor
  ~Function() {}
};

#endif /* functions_hpp */
