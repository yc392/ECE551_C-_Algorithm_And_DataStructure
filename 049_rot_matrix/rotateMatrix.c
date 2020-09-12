#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int readFile(FILE * f, int row[]) {
  int c;
  int i = 0;
  for (;;) {
    c = fgetc(f);
    if (c == '\n') {
      if (i != 10) {
        fprintf(stderr, "too few elements\n");
        exit(EXIT_FAILURE);
      }
      return 0;
    }
    else if (c == EOF) {
      if (i != 10) {
        fprintf(stderr, "too few elements\n");
        exit(EXIT_FAILURE);
      }
      return 1;
    }
    else {
      if (i < 10) {
        row[i++] = c;
      }
      else {
        fprintf(stderr, "too much elements\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

void rowError(FILE * f) {
  int b;
  while ((b = fgetc(f)) != EOF) {
    fprintf(stderr, "too much rows\n");
    exit(EXIT_FAILURE);
  }
}

void rotate(int a[10][10]) {
  int b[10][10] = {0};
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      b[i][j] = a[9 - j][i];
      printf("%c", b[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  int matrix[10][10] = {0};
  // int a[1][10] = {0};
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  // int j = 0;
  for (int i = 0; i < 10; i++) {
    readFile(f, matrix[i]);
  }
  /*if (readFile(f, matrix[9]) != 1) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }*/
  rowError(f);
  rotate(matrix);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
