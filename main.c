#include "structs.h"
#include "hash.h"
#include "lists.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//./main {files.txt}
int main(int argc, char const *argv[]) {
  init_table();
  int file = 1;
  int opcao;
  printf("[1] START\n");
  printf("[2] QUIT\n");
  printf("Opcao: ");
  scanf("%d", &opcao);

  system("clear");

  if (argc == 1) {
    printf("ERROR! NO FILES TO EXECUTE\n");
    return 0;
  }
  while (argv[file] != NULL && opcao != 2) {
    system("clear");
    printf("File: %d \n", file);
    printf("\n");

    FILE *fp;
    fp = fopen(argv[file], "r");
    if (fp == NULL) {
      printf("FILE ERROR\n");
      return 0;
    }
    ILIST lista = readList(fp);
    fclose(fp);

    printf("Lista %d: \n", file);
    printList(lista);
    printf("\n----------Execução------------\n");
    execlist(lista);
    ++file;
    printf("------------------------------\n\n");
    if (argv[file] != NULL) {
      printf("[1] CONTINUE\n");
      printf("[2] QUIT\n");
      printf("Opcao: ");
      scanf("%d", &opcao);
      printf("\n");
    }
  }
  return 0;
}
