#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int findKey(FILE * f) {
  int c;
  int a[26] = {0};
  int maxE = 0;
  int indexE;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      a[c]++;
    }
  }
  for (int i = 0; i < 26; i++) {
    if (a[i] > maxE) {
      maxE = a[i];
      indexE = i;
    }
  }
  int key = (indexE + 22) % 26;

  return key;
}

/*void encrypt(FILE * f, int key) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    //    printf("sb");
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      c -= key;
      if (c < 0) {
        c += 26;
      }
      c %= 26;
      c += 'a';
    }
    printf("%c", c);
  }
  }*/

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  int key;

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  key = findKey(f);

  printf("%d", key);

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
