#include <stdio.h>
#include <stdlib.h>

int compare(int a, int b) {
  if (b > a) {
    return b;
  }
  else {
    return a;
  }
}

size_t maxSeq(int * array, size_t n) {
  size_t maxLength = 1;
  int increaseLength = 1;
  if (n == 0) {
    maxLength = 0;
    return maxLength;
  }
  for (size_t i = 1; i < n; i++) {
    int a = *array;
    array++;
    int b = *array;
    if (a < b) {
      increaseLength++;
      maxLength = compare(maxLength, increaseLength);
    }
    if (a >= b) {
      increaseLength = 1;
    }
  }
  return maxLength;
}
