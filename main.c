#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//./main file.txt
int main(int argc, char const *argv[]) {
  FILE *fp;
  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("FILE ERROR\n");
    return 0;
  }
  char* buffer = NULL;
  size_t buffsize = 32;
  size_t aux;
  aux = getline(&buffer, &buffsize, fp);
  removeSpaces(buffer);
  printf("%s", buffer);
  return 0;
}
