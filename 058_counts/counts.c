#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * count = malloc(sizeof(*count));
  count->arrCount = NULL;
  count->length = 0;
  count->unKnown = 0;
  return count;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  one_count_t * p;
  size_t i;
  if (name == NULL) {
    c->unKnown++;
    return;
  }
  for (i = 0; i < c->length; i++) {
    p = &c->arrCount[i];
    if (strcmp(p->oneString, name) == 0) {
      p->count++;
      break;
    }
  }
  if (i == c->length) {
    c->arrCount = realloc(c->arrCount, (c->length + 1) * sizeof c->arrCount[0]);
    p = &c->arrCount[c->length++];

    p->oneString = strdup(name);
    p->count = 0;
    p->count++;
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  size_t i;
  one_count_t * p;

  for (i = 0; i < c->length; i++) {
    p = &c->arrCount[i];
    fprintf(outFile, "%s: %d\n", p->oneString, p->count);
  }
  if (c->unKnown > 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unKnown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  one_count_t * p;

  for (size_t i = 0; i < c->length; i++) {
    p = &c->arrCount[i];
    free(p->oneString);
  }
  free(c->arrCount);
  free(c);
}
