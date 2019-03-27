#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Elem mkVar(char* s){
  Elem new;
  new.kind = STRING;
  new.content.name = strdup(s);
  return new;
}

Elem mkInt(int x){
  Elem new;
  new.kind = INT_CONST;
  new.content.val = x;
  return new;
}

Elem empty(){
  Elem new;
  new.kind = EMPTY;
  return new;
}

Instr mkInstr(OpKind oper, Elem x, Elem y, Elem z){
  Instr new;
  new.op = oper;
  new.first = x;
  new.second = y;
  new.third = z;
  return new;
}

ILIST mkList(Instr n, ILIST l1) {
   ILIST l = malloc(sizeof(struct list));
   l->head = n;
   l->tail = l1;
   return l;
}

//-----------------Getters-------------------------

Instr head(ILIST l) {
   return l->head;
}

ILIST tail(ILIST l) {
   return l->tail;
}


int getVal(Elem x){
  if (x.kind == INT_CONST) {
    return x.content.val;
  }
  return 0;
}

char* getName(Elem x){
  if (x.kind == STRING) {
    return x.content.name;
  }
  return NULL;
}

//-----------Hash Funcs---------------------------

unsigned int hash(char* str){
  unsigned int h;
  unsigned char *p;
  h = 0;
  for(p = (unsigned char*)str; *p != '\0'; p++){
    h = MULTIPLIER * h + *p;
  }
  return h % HASH_SIZE;
}

void init(){
  for(int i = 0; i < HASH_SIZE; i++){
    table[i] = NULL;
  }
}

void display() {
  int i = 0;
  for(i = 0; i < HASH_SIZE; i++){
    if (table[i] != NULL) {
      printf("[%s, %d]\n", table[i]->key, table[i]->value);
    }
  }
}

List* lookup(char* k){
    int index = hash(k);
    while (table[index] != NULL) {
      if(table[index]->key == k){
        return table[index];
      }
      index++;
      index %= HASH_SIZE;
    }
    return NULL;
}

void insert(char* k, int val){
  int index;
  List* new = (List*)malloc(sizeof(struct List));
  index = hash(k);
  new->key = k;
  new->value = val;
  new->next = table[index];
  table[index] = new;
}

//-------------PRINTLIST------------------

void printList(ILIST l) {
  while (l != NULL) {
    escrever(head(l));
    l = l->tail;
  }
  printf("\n");
}

void escrever(Instr inst) {
  switch (inst.op) {
    case ATRIB:
    if (inst.second.kind == INT_CONST) {
      printf("%s = %d\n", getName(inst.first), getVal(inst.second));
    } else if (inst.second.kind == STRING) {
      printf("%s = %s\n", getName(inst.first), getName(inst.second));

    }
    break;
    case ADD:
    if (inst.second.kind == INT_CONST && inst.third.kind == INT_CONST) {
      printf("%s = %d + %d\n", getName(inst.first), getVal(inst.second), getVal(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == STRING) {
      printf("%s = %s + %s\n", getName(inst.first), getName(inst.second), getName(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == INT_CONST) {
      printf("%s = %s + %d\n", getName(inst.first), getName(inst.second), getVal(inst.third));
      break;
    }
    if (inst.second.kind == INT_CONST && inst.third.kind == STRING) {
      printf("%s = %d + %s\n", getName(inst.first), getVal(inst.second), getName(inst.third));
      break;
    }
    break;
    case SUB:
    if (inst.second.kind == INT_CONST && inst.third.kind == INT_CONST) {
      printf("%s = %d - %d\n", getName(inst.first), getVal(inst.second), getVal(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == STRING) {
      printf("%s = %s - %s\n", getName(inst.first), getName(inst.second), getName(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == INT_CONST) {
      printf("%s = %s - %d\n", getName(inst.first), getName(inst.second), getVal(inst.third));
      break;
    }
    if (inst.second.kind == INT_CONST && inst.third.kind == STRING) {
      printf("%s = %d - %s\n", getName(inst.first), getVal(inst.second), getName(inst.third));
      break;
    }
    break;
    case MUL:
    if (inst.second.kind == INT_CONST && inst.third.kind == INT_CONST) {
      printf("%s = %d * %d\n", getName(inst.first), getVal(inst.second), getVal(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == STRING) {
      printf("%s = %s * %s\n", getName(inst.first), getName(inst.second), getName(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == INT_CONST) {
      printf("%s = %s * %d\n", getName(inst.first), getName(inst.second), getVal(inst.third));
      break;
    }
    if (inst.second.kind == INT_CONST && inst.third.kind == STRING) {
      printf("%s = %d * %s\n", getName(inst.first), getVal(inst.second), getName(inst.third));
      break;
    }
  }
}

void removeSpaces(char* source){
  char* i = source;
  char* j = source;
  while(*j != 0)
  {
    *i = *j++;
    if(*i != ' ')
      i++;
  }
  *i = 0;
}
