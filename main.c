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
  char* buffer = NULL;
  size_t buffsize = 32;
  ssize_t aux;
  int i = 1;
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
    ILIST listastart = mkList(mkInstr(START,empty(),empty(),empty(),0, 0),NULL);
    ILIST lista = listastart;
    while ((aux = getline(&buffer, &buffsize, fp)) != -1) {
      removeSpaces(buffer);
      Instr inst = parseInstr(buffer, i);
      i++;
      lista = addLast(inst, lista);
    }

    fclose(fp);
    printf("Lista: \n");
    printList(lista);
    printf("\n----------Execução------------\n");
    //Percorrer Lista
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
