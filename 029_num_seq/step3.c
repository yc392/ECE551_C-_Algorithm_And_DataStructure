#include <stdio.h>
#include <stdlib.h>
// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
int seq3(int x, int y) {
  int a = -3 * x + (2 + x) * y;
  return a;
}

int countEvenInSeq3Range(int, int, int, int);

void testCountEven(int a, int b, int c, int d) {
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         a,
         b,
         c,
         d,
         countEvenInSeq3Range(a, b, c, d));
}
//  Step 3 (B): write main to test seq3
int main(void) {
  for (int i = -3; i < 3; i++) {
    for (int j = -3; j < 3; j++) {
      printf("seq3(%d,%d) = %d\n", i, j, seq3(i, j));
    }
  }
  testCountEven(0, 2, 0, 3);
  testCountEven(0, 0, 5, 10);
  testCountEven(0, -1, 2, 10);
  testCountEven(-1, 2, -2, 3);
  return EXIT_SUCCESS;
}
//  Step 3 (C): write countEvenInSeq3Range
int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  int numEven = 0;
  if (xLow >= xHi || yLow >= yHi) {
    return numEven;
  }
  for (int i = xLow; i < xHi; i++) {
    for (int j = yLow; j < yHi; j++) {
      if (seq3(i, j) % 2 == 0) {
        numEven++;
      }
    }
  }
  return numEven;
}
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range

//
// Be sure to #include any header files you need!
