#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * outputName;
  size_t length = strlen(inputName);

  outputName = malloc(length + 8);
  memcpy(outputName, inputName, length);
  memcpy(outputName + length, ".counts", 8);
  return outputName;
}
