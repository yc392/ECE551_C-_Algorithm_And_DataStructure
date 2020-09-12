#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getPair(kvpair_t * pair, char * line) {
  const char *p, *q;

  p = strchr(line, '=');

  pair->key = strndup(line, (size_t)(p - line));
  q = strchr(++p, '\n');
  pair->value = strndup(p, (size_t)(q - p));
  //  printf("%s", pair->value);
  /*  if (singlePair->key == NULL || singlePair->value == NULL) {
    goto fail;
    }*/
  return;
}

kvarray_t * readKVs(const char * fname) {
  char * line = NULL;
  size_t numLine = 0;
  kvarray_t * array = NULL;
  kvpair_t * pair = NULL;
  size_t numPair = 0;

  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }

  while (getline(&line, &numLine, f) != -1) {
    pair = realloc(pair, (numPair + 1) * sizeof(*pair));
    getPair(&pair[numPair++], line);
    //pair = &pair[numPair++];
    //numPair++;
  }
  free(line);
  array = malloc(sizeof(*array));
  array->length = numPair;
  array->arrayPair = pair;

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    exit(EXIT_FAILURE);
  }
  return array;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME

  for (size_t i = 0; i < pairs->length; i++) {
    free(pairs->arrayPair[i].key);
    free(pairs->arrayPair[i].value);
  }
  free(pairs->arrayPair);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  kvpair_t * p;

  for (size_t i = 0; i < pairs->length; i++) {
    p = &pairs->arrayPair[i];
    printf("key = '%s' value = '%s'\n", p->key, p->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME

  kvpair_t * p;
  for (size_t i = 0; i < pairs->length; i++) {
    p = &pairs->arrayPair[i];
    if (strcmp(key, p->key) == 0) {
      return p->value;
    }
  }
  return NULL;
}
