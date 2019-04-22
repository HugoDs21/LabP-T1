#include "lists.h"
#include "hash.h"
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

void execlist(ILIST lista) {
  ILIST listastart = lista;
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
      printf("%d \n",val);
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

}
