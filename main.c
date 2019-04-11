#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    while (lista != NULL) {
      Instr i = head(lista);
      Instr g;
      char* lab;
      List* li;
      int val, a1, a2;
      switch(i.op){
        case START:
        break;
        case QUIT:
        lista->tail = NULL;
        break;
        case PRINT:
        li = lookup(getName(i.first));
        val = getHashValue(li);
        printf("%d \n", val);
        break;
        case READ:
        printf("Valor de %s = ", getName(i.first));
        scanf("%d", &val);
        insert(getName(i.first), val);
        break;
        case IF:
        li = lookup(getName(i.first));
        val = getHashValue(li);
        if (val == 0) {
          lista = lista->tail;
        }
        break;
        case GOTO:
        lista = listastart;
        lab = getName(i.first);
        a1 = getIndex(lab, listastart);
        //lista = lista->tail;
        g = head(lista);
        while (a1 != g.index) {
          lista = lista->tail;
          g = head(lista);
        }
        break;
        case LABEL:
        break;
        case ATRIB:
        insert(getName(i.first), getVal(i.second));
        break;
        case ADD:
        switch (i.type) {
          case 1:
          a1 = getHashValue(lookup(getName(i.second)));
          a2 = getHashValue(lookup(getName(i.third)));
          insert(getName(i.first), (a1 + a2));
          break;
          case 2:
          insert(getName(i.first), (getVal(i.second) + getVal(i.third)));
          break;
          case 3:
          a1 = getHashValue(lookup(getName(i.second)));
          insert(getName(i.first), (a1 + getVal(i.third)));
          break;
          case 4:
          a2 = getHashValue(lookup(getName(i.third)));
          insert(getName(i.first), (a2 + getVal(i.second)));
          break;
        }
        break;
        case SUB:
        switch (i.type) {
          case 1:
          a1 = getHashValue(lookup(getName(i.second)));
          a2 = getHashValue(lookup(getName(i.third)));
          insert(getName(i.first), (a1 - a2));
          break;
          case 2:
          insert(getName(i.first), (getVal(i.second) - getVal(i.third)));
          break;
          case 3:
          a1 = getHashValue(lookup(getName(i.second)));
          insert(getName(i.first), (a1 - getVal(i.third)));
          break;
          case 4:
          a2 = getHashValue(lookup(getName(i.third)));
          insert(getName(i.first), (a2 - getVal(i.second)));
          break;
        }
        break;
        case MUL:
        switch (i.type) {
          case 1:
          a1 = getHashValue(lookup(getName(i.second)));
          a2 = getHashValue(lookup(getName(i.third)));
          insert(getName(i.first), (a1 * a2));
          break;
          case 2:
          insert(getName(i.first), (getVal(i.second) * getVal(i.third)));
          break;
          case 3:
          a1 = getHashValue(lookup(getName(i.second)));
          insert(getName(i.first), (a1 * getVal(i.third)));
          break;
          case 4:
          a2 = getHashValue(lookup(getName(i.third)));
          insert(getName(i.first), (a2 * getVal(i.second)));
          break;
        }
        break;
      }
      lista = lista->tail;
    }
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
