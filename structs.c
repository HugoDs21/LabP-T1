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

//--------------List-----------------------

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

void init_table(){
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

List* lookup(char* s){
    int index = hash(s);
    while (table[index] != NULL) {
      if (table[index]->key == s) {
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

int getHashValue(List* p){
  return p->value;
}

char* getHashKey(List* p){
  return p->key;
}

//--------------------FUNCS-----------------------------------------------


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
    break;
    case READ:
      printf("Ler(%s)\n", getName(inst.first));
      break;
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

Instr parseInstr(char* s){
  Instr i;
  char* aux = malloc(sizeof(char));
  //READ ler(k)
  if (strstr(s, "ler") != NULL) {
    *aux = *(s+4);
    i = mkInstr(READ, mkVar(aux), empty(), empty());
    return i;
  }
  //ATRIB
  if(strlen(s) <= 4){
    *aux = *(s+0);
    Elem var = mkVar(aux);
    *aux = *(s+2);
    Elem val = mkInt(atoi(aux));
    i = mkInstr(ATRIB,var,val,empty());
    return i;
  }
  //Contas
  if (strlen(s) <= 6) {
    switch (*(s+3)) {
      case '+':
        strcpy(aux,s);
        aux = strtok(aux, "=");
        Elem var = mkVar(aux);
        aux = strtok(NULL, "+");
        Elem val1 = mkInt(atoi(aux));
        aux = strtok(NULL, ";");
        Elem val2 = mkInt(atoi(aux));
        i = mkInstr(ADD,var,val1,val2);
        return i;
    }
  }
  return i;
}
