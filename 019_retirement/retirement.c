#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  int year = startAge / 12;
  int month = startAge % 12;
  printf("Age %3d month %2d you have $%.2lf\n", year, month, initial);

  for (int i = 0; i < working.months; i++) {
    startAge++;
    initial += (working.contribution + initial * (working.rate_of_return));
    year = startAge / 12;
    month = startAge % 12;
    printf("Age %3d month %2d you have $%.2lf\n", year, month, initial);
  }

  for (int j = 1; j < retired.months; j++) {
    startAge++;
    initial += (retired.contribution + initial * (retired.rate_of_return));
    year = startAge / 12;
    month = startAge % 12;
    printf("Age %3d month %2d you have $%.2lf\n", year, month, initial);
  }
}

int main(void) {
  retire_info a, b;

  a.months = 489;
  a.contribution = 1000;
  a.rate_of_return = (0.045 / 12);

  b.months = 384;
  b.contribution = -4000;
  b.rate_of_return = (0.01 / 12);

  retirement(327, 21345, a, b);
  return EXIT_SUCCESS;
}
