#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//./main file.txt
int main(int argc, char const *argv[]) {
  init_table();
  char* buffer = NULL;
  size_t buffsize = 32;
  ssize_t aux;
  int i = 1;
  int f = 1;
  while (argv[f] != NULL) {
    printf("File: %d \n", f);
    printf("\n");
    FILE *fp;
    fp = fopen(argv[f], "r");
    if (fp == NULL) {
      printf("FILE ERROR\n");
      return 0;
    }
    ILIST lista = mkList(mkInstr(START,empty(),empty(),empty(),0, 0),NULL);
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
        // while (lista != NULL) {
        //   lista = lista->tail;
        // }
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
        lab = getName(i.first);
        a1 = getIndex(lab, lista);
        lista = lista->tail;
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
    ++f;
    printf("------------------------------\n\n");
  }
  return 0;
}
