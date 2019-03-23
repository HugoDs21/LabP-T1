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

ILIST newList(Instr head, ILIST* head_l){
  ILIST new;
  new.elem = head;
  new.next = head_l;
  return new;
}

int getVal(Elem x){
  if (x.kind == INT_CONST) {
    return x.content.val;
  }
}

char* getName(Elem x){
  if (x.kind == STRING) {
    return x.content.name;
  }
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
  }
}
