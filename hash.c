#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int getHashValue(List* p){
  return p->value;
}

char* getHashKey(List* p){
  return p->key;
}

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
  int i = 0;
  for(i; i < HASH_SIZE; i++){
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
    if (table[index]->key) {
      return table[index];
    }
    index ++;
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
