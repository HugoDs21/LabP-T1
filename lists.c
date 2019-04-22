#include "lists.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

ILIST mkList(Instr n, ILIST l1) {
  ILIST l = malloc(sizeof(struct list));
  l->head = n;
  l->tail = l1;
  return l;
}

ILIST append(ILIST l1, ILIST l2){
  ILIST new = l1;
  if(l1 == NULL) return l2;
  while (l1->tail != NULL) {
    l1 = l1->tail;
  }
  l1->tail = l2;
  return new;
}

ILIST addLast(Instr n, ILIST l1){
  ILIST l2 = mkList(n,NULL);
  ILIST new = append(l1,l2);
  return new;
}

void printList(ILIST l) {
  while (l != NULL) {
    escrever(head(l));
    l = l->tail;
  }
}

Instr head(ILIST l) {
  return l->head;
}

ILIST tail(ILIST l) {
  return l->tail;
}

int getIndex(char* s, ILIST lista){
  Instr i;
  while(lista != NULL){
    i = head(lista);
    if(i.op == LABEL){
      if (strcmp(s, getName(i.first)) == 0) {
        return i.index;
      }
    }
    lista = lista->tail;
  }
  return 0;
}
