#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned a, unsigned b, unsigned expected_ans) {
  if (power(a, b) != expected_ans) {
    printf("Something wrong with run_check (%u,%u,%u)", a, b, expected_ans);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_check(0, 0, 1);
  run_check(1, 0, 1);
  run_check(-1, 0, 1);
  run_check(1, 100000, 1);
  run_check(10000000, 1, 10000000);
  run_check(0, 1, 0);
  run_check(2, 2, 4);
  return EXIT_SUCCESS;
}
