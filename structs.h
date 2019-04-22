#ifndef __GUARD_STRUCTS__
#define __GUARD_STRUCTS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum  {START, QUIT, ATRIB, ADD, SUB, MUL, PRINT, READ, IF, GOTO, LABEL} OpKind;
typedef enum {INT_CONST, STRING, EMPTY} ElemKind;

typedef struct{
  ElemKind kind;
  union
  {
    int val;
    char* name;
  }content;
} Elem;

typedef struct{
  OpKind op;
  Elem first, second, third;
  int type, index;
} Instr;

Elem mkVar(char*);
Elem mkInt(int);
Elem empty();
Instr mkInstr(OpKind, Elem, Elem, Elem, int, int);
int getVal(Elem );
char* getName(Elem);
void escrever(Instr);
void removeSpaces(char*);
Instr parseInstr(char*, int);
int getType(char*, char*);

#endif
