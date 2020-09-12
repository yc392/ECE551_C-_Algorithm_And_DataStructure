#include <stdio.h>
#include <stdlib.h>
// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
int seq1(int x) {
  int a = -3 + 4 * x;
  return a;
}

void printSeq1Range(int, int);

void testSeqRange(int a, int b) {
  printf("printSeq1Range(%d, %d)\n", a, b);
  printSeq1Range(a, b);
}

//  Step 1 (B): write main to test seq1
int main(void) {
  for (int i = -10; i < 10; i++) {
    printf("seq1(%d) = %d\n", i, seq1(i));
  }

  testSeqRange(0, 4);
  testSeqRange(-2, 6);
  testSeqRange(7, 3);
  testSeqRange(0, 0);
  testSeqRange(5, 5);
  return EXIT_SUCCESS;
}
//  Step 1 (C): write printSeq1Range
void printSeq1Range(int low, int high) {
  if (low >= high) {
    printf("\n");
  }
  else {
    for (int i = low; i < high - 1; i++) {
      printf("%d, ", seq1(i));
    }
    printf("%d\n", seq1(high - 1));
  }
}
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!
