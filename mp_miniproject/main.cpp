//
//  main.cpp
//  FP
//
//  Created by Yuhua Cai on 2019/12/2.
//  Copyright © 2019 Yuhua Cai. All rights reserved.
//

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <stack>
#include <vector>

#include "expr.hpp"
#include "functions.hpp"
#include "helper.hpp"
#include "step2.hpp"
#include "step3.hpp"

using namespace std;

//Step 4 Implementation

//struct for 2D gradient vector
struct vect2d_tag {
  double dx;
  double dy;
};
typedef struct vect2d_tag vect2d;

//strcut for 2D points
struct point2d_tag {
  double x;
  double y;
};
typedef struct point2d_tag point2d;

//Calculating gradient at certain point(x, y)
vect2d gradient(list<Function> funclist, double x, double y) {
  vect2d result;
  //dx/dy set to 0.0001
  double h = 0.0001;
  string sx = to_string(x);
  string sy = to_string(y);

  string sh = to_string(h);
  string hx = to_string(x + h);
  string hy = to_string(y + h);
  stringstream exprX;
  exprX << "( / (- (f " << hx << " " << sy << ") (f " << sx << " " << sy << ") ) " << sh
        << ")";
  string fxderiv = complicatedDef(exprX.str(), funclist);
  stringstream exprY;
  exprY << "( / (- (f " << sx << " " << hy << ") (f " << sx << " " << sy << ") ) " << sh
        << ")";
  string fyderiv = complicatedDef(exprY.str(), funclist);
  result.dx = stod(fxderiv);
  result.dy = stod(fyderiv);
  return result;
}

//Euclidean distance calculate
double euclideanDistance(point2d original, point2d resulted) {
  return sqrt(pow((original.x - resulted.x), 2) + pow((original.y - resulted.y), 2));
}

//To find the next point after one step
point2d gradientCal(list<Function> funcs,
                    point2d startPoint,
                    double gamma,
                    double convergedDistance,
                    long stepLimit,
                    bool ascent) {
  point2d resultPoint = startPoint;
  vect2d grad;
  for (int i = 0; i < stepLimit; i++) {
    grad = gradient(funcs, resultPoint.x, resultPoint.y);
    //Ascent
    if (ascent) {
      point2d originalPoint = resultPoint;

      resultPoint.x = resultPoint.x + gamma * grad.dx;
      resultPoint.y = resultPoint.y + gamma * grad.dy;
      if (euclideanDistance(originalPoint, resultPoint) < convergedDistance) {
        break;
      }
    }
    //Descent
    else {
      point2d originalPoint = resultPoint;

      resultPoint.x = resultPoint.x - gamma * grad.dx;
      resultPoint.y = resultPoint.y - gamma * grad.dy;
      if (euclideanDistance(originalPoint, resultPoint) < convergedDistance) {
        break;
      }
    }
  }
  return resultPoint;
}

//main function
int main(void) {
  list<Function> funcList;  //A list of Functions
  char * line = NULL;
  size_t sz;

  //get lines of command from user
  while (getline(&line, &sz, stdin) != -1) {
    const char * temp = line;
    string getline(temp);

    //switch case for different modes
    int mode = 0;
    if (getline.find("define") != (size_t)-1) {
      mode = 1;  //mode "define"
    }
    else if (getline.find("test") != (size_t)-1) {
      mode = 2;  //mode "test"
    }
    else if (getline.find("numint") != (size_t)-1) {
      mode = 3;  //mode "numint"
    }
    else if (getline.find("mcint") != (size_t)-1) {
      mode = 4;  //mode "mcint"
    }
    else if ((getline.find("min") != (size_t)-1) || (getline.find("max") != (size_t)-1))
      mode = 5;  //mode "min" or "max"

    switch (mode) {
      case 1: {
        std::list<std::string> var;
        string afterEq;

        var = variable(&temp);     //get variables
        string name = var.back();  //get function name
        var.pop_back();
        string s(temp);
        std::size_t eq = s.find("=");
        string beforeEq = s.substr(0, eq);
        afterEq = finalExpr(s.substr(eq + 1));  //get function Expression

        const Function * function = new Function(name, var, afterEq);
        funcList.push_front(*function);  //push function to the list
        delete function;
        cout << beforeEq << "\n";
        break;
      }

      //Step 1: Parsing functions
      case 2: {
        string s(temp);
        //Stack using to find correspond brackets for the First part
        stack<int> ministack;
        int startSub = 0;
        int endSub = 0;
        for (int i = 0; (size_t)i < s.length(); i++) {
          if (s[i] == '(') {
            int j = i;
            ministack.push(j);
          }
          if (s[i] == ')') {
            startSub = ministack.top();
            ministack.pop();
            if (ministack.empty()) {
              endSub = i;
              break;
            }
          }
        }
        string lhs = s.substr(startSub, endSub - startSub + 1);

        s = finalExpr(s);  //function invoke for check build-in functions
        s = complicatedDef(
            s, funcList);  //function invoke to deal with complicated definition

        //get answer
        const size_t len = s.length();
        char * cstr = new char[len + 1];
        strcpy(cstr, s.c_str());
        char * p = strtok(cstr, " ");
        string ans[3];
        int k = 0;
        while (p != NULL) {
          string s(p);
          ans[k] = s;
          p = strtok(NULL, " ");
          k++;
        }
        delete[] cstr;
        std::stringstream answer;

        //Result output
        if (equals(ans[1], ans[2])) {
          answer << lhs << " = " << stod(ans[1]) << " [correct]\n";
          cout << answer.str();
        }
        else {
          answer << lhs << " = " << stod(ans[1]) << " [INCORRECT: expected "
                 << stod(ans[2]) << "]\n";
          cout << answer.str();
        }
        break;
      }

      //Step 2: Numerical Integration
      case 3: {
        string s(temp);
        //find the correspond function
        Function found = findFunction(s, funcList);
        //parse the command to get arguments
        list<string> argNumint = parseNumint(s);
        argNumint.pop_back();
        string stepSzie = argNumint.back();
        vector<vector<double> > points = pointList(s, funcList);
        //invoke recursivecall to get Numerical Integration
        double result = recursiveCall(points, found, stepSzie);
        cout << "The result is: " << result << "\n";

        break;
      }

      //Step 3: Monte Carlo Integration
      case 4: {
        string s(temp);
        double ans = 0;
        //invoke calculateMcint to get Monte Carlo Integration
        ans = calculateMcint(s, funcList);
        cout << "The result is: " << ans << "\n";
        break;
      }

      //Step 4: Gradient Ascent/Descent
      case 5: {
        //Ascent or Descent
        bool ascent = true;
        if (getline.find("min") != (size_t)-1) {
          ascent = false;
        }
        //find correspond function
        Function found = findFunction(getline, funcList);
        //parse command to obtain arguments
        list<string> argNumint = parseNumint(getline);
        argNumint.pop_back();
        double gamma = stod(argNumint.back());
        argNumint.pop_back();
        double convergedDistance = stod(argNumint.back());
        argNumint.pop_back();
        point2d startPoint;
        startPoint.x = stod(argNumint.back());
        argNumint.pop_back();
        startPoint.y = stod(argNumint.back());
        argNumint.pop_back();
        long stepLimit = stod(argNumint.back());
        //invoke gradientcal to get resultpoint
        point2d resultPoint = (gradientCal(
            funcList, startPoint, gamma, convergedDistance, stepLimit, ascent));
        cout << "The result point is: (" << resultPoint.x << " ," << resultPoint.y
             << ")\n";
      }
    }
  }

  free(line);  //free memory
  return EXIT_SUCCESS;
}
