#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_SIZE 100
#define MULTIPLIER 31

typedef struct List List;
struct List{
  char* key;
  int value;
  List* next;
};

List* table[HASH_SIZE];

unsigned int hash(char*);
List* lookup(char*);
void insert(char*, int);
void display();
void init_table();
int getHashValue(List*);
char* getHashKey(List*);
