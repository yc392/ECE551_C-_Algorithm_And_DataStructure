#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int *, size_t);

void check(int * array, size_t n, size_t expect) {
  if (maxSeq(array, n) != expect) {
    printf("Something wrong with maxSeq");
    exit(EXIT_FAILURE);
  }
}

int main() {
  int a[0] = {};
  check(a, 0, 0);
  int b[3] = {1, 1, 1};
  check(b, 3, 1);
  int c[4] = {0, 1, 2, 3};
  check(c, 4, 4);
  int d[4] = {-3, -2, -1};
  check(d, 3, 3);
  int e[10] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  check(e, 10, 4);
  int f[2] = {-1, 1};
  check(f, 2, 2);
  return EXIT_SUCCESS;
}
