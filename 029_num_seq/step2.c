#include <stdio.h>
#include <stdlib.h>
// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
int seq2(int x) {
  if ((x - 2) % 4 == 0) {
    int a = 2 * x;
    return a;
  }
  int a = x * (x + 3) + 1;
  return a;
}
//  Step 2 (B): write main to test seq2
int sumSeq2(int, int);

void testSumSeq(int a, int b) {
  printf("sumSeq2(%d, %d) = %d\n", a, b, sumSeq2(a, b));
}

int main(void) {
  for (int i = -10; i < 15; i++) {
    printf("seq2(%d) = %d\n", i, seq2(i));
  }
  testSumSeq(0, 2);
  testSumSeq(3, 6);
  testSumSeq(9, 7);
  testSumSeq(0, 0);
  return EXIT_SUCCESS;
}

//  Step 2 (C): write sumSeq2
int sumSeq2(int low, int high) {
  int sum = 0;
  if (low >= high) {
    return 0;
  }
  else {
    for (int i = low; i < high; i++) {
      sum += seq2(i);
    }
    return sum;
  }
}
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!
