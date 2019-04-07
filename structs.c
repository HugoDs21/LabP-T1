#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

Instr mkInstr(OpKind oper, Elem x, Elem y, Elem z, int t, int ind){
  Instr new;
  new.op = oper;
  new.first = x;
  new.second = y;
  new.third = z;
  new.type = t;
  new.index = ind;
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
    if (table[index]->key, s) {
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
    case PRINT:
    printf("Escrever(%s)\n", getName(inst.first));
    break;
    case START:
    break;
    case QUIT:
    printf("Quit\n");
    break;
    case IF:
    printf("If %s\n", getName(inst.first));
    break;
    case GOTO:
    printf("Goto %s\n", getName(inst.first));
    break;
    case LABEL:
    printf("Label %s\n", getName(inst.first));
    break;
  }
}

void removeSpaces(char* str){
  str[strlen(str)-2] = '\0';
  int count = 0;
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i];
    str[count] = '\0';
}

int getType(char* str, char* ch){
  //TIPOS
  //Tipo 1 = str str
  //Tipo 2 = int int
  //Tipo 3 = str int
  //Tipo 4 = int str
  char *token, *string, *var1, *var2, *dup1, *dup2;
  int tmp1,tmp2, tipo;
  string = strdup(str);
  if (string == NULL)
  return -1;

  token = strsep(&string, "=");
  token = strsep(&string, "=");
  //////token[strlen(token)-1] = '\0'; // remove ";"
  dup1 = strdup(token);
  dup2 = strdup(token);

  var1 = strsep(&dup1, ch);
  if((var1[0] >= 0x60 && var1[0] <= 0x7B)) // detect string
  {
    var1 = strsep(&dup1, ch);
    if((var1[0] >= 0x61 && var1[0] <= 0x7A)){
      tipo = 1;
      return tipo;
    }
    else {
      tmp2 = atoi(var1);
      tipo = 3;
      return tipo;
    }
  }

  var2 = strsep(&dup2, ch);
  if(!(var2[0] >= 0x60 && var2[0] <= 0x7B)){
    tmp1 = atoi(var2);
    var2 = strsep(&dup2, ch);
    if(!(var2[0] >= 0x61 && var2[0] <= 0x7A)){
      tmp2 = atoi(var2);
      tipo = 2;
      return tipo;
    }
    else {
      tipo = 4;
      return tipo;
    }
  }
}

Instr parseInstr(char* s, int index){
  Instr i;
  //QUIT quit
  if (strstr(s, "quit") != NULL) {
    i = mkInstr(QUIT,empty(),empty(),empty(),0, index);
    return i;
  }
  //READ ler(k)
  if (strstr(s, "ler") != NULL) {
    char* string = strdup(s);
    char* aux = strsep(&string, "(");
    aux = strsep(&string, ")");
    Elem ch = mkVar(aux);
    i = mkInstr(READ,ch,empty(),empty(),0, index);
    return i;
  }
  //PRINT escrever(p)
  if (strstr(s, "escrever") != NULL) {
    char* string = strdup(s);
    char* aux = strsep(&string, "(");
    aux = strsep(&string, ")");
    Elem ch = mkVar(aux);
    i = mkInstr(PRINT,ch,empty(),empty(),0, index);
    return i;
  }
  //IF if: k
  if (strstr(s, "if") != NULL) {
    char* string = strdup(s);
    char* aux = strsep(&string, ":");
    aux = strsep(&string, ":");
    Elem ch = mkVar(aux);
    i = mkInstr(IF,ch, empty(), empty(), 0, index);
    return i;
  }
  //GOTO goto: L1
  if (strstr(s, "goto") != NULL) {
    char* string = strdup(s);
    char* aux = strsep(&string, ":");
    aux = strsep(&string, ":");
    Elem ch = mkVar(aux);
    i = mkInstr(GOTO,ch,empty(),empty(),0, index);
    return i;
  }
  //LABEL label: L1
  if (strstr(s, "label") != NULL) {
    char* string = strdup(s);
    char* aux = strsep(&string, ":");
    aux = strsep(&string, ":");
    Elem ch = mkVar(aux);
    i = mkInstr(LABEL,ch,empty(),empty(),0, index);
    return i;
  }
  //ATRIB s = 2;
  if (strstr(s, "+") == NULL &&
      strstr(s, "-") == NULL &&
      strstr(s, "*") == NULL &&
      strstr(s, "/") == NULL) {
    char* string = strdup(s);
    char* aux = strsep(&string, "=");
    Elem var = mkVar(aux);
    aux = strsep(&string, ";");
    Elem num = mkInt(atoi(aux));
    i = mkInstr(ATRIB,var,num,empty(),0, index);
    return i;
  }
  //CONTAS
  if(strstr(s, "+") != NULL){ //ADD
    int t = getType(s, "+");
    char *token, *string, *var;
    switch (t) {
      case 1:
      string = strdup(s);
      token = strsep(&string, "=");
      Elem v1 = mkVar(token);
      token = strsep(&string, "=");
      //token[strlen(token)-1] = '\0';
      var = strsep(&token, "+");
      Elem s11 = mkVar(var);
      var = strsep(&token, "+");
      Elem s21 = mkVar(var);
      i = mkInstr(ADD,v1,s11,s21,t, index);
      return i;
      break;
      case 2:
      string = strdup(s);
      token = strsep(&string, "=");
      Elem v2 = mkVar(token);
      token = strsep(&string, "=");
      //token[strlen(token)-1] = '\0';
      var = strsep(&token, "+");
      Elem s12 = mkInt(atoi(var));
      var = strsep(&token, "+");
      Elem s22 = mkInt(atoi(var));
      i = mkInstr(ADD,v2,s12,s22,t, index);
      return i;
      break;
      case 3:
      string = strdup(s);
      token = strsep(&string, "=");
      Elem v3 = mkVar(token);
      token = strsep(&string, "=");
      //token[strlen(token)-1] = '\0';
      var = strsep(&token, "+");
      Elem s13 = mkVar(var);
      var = strsep(&token, "+");
      Elem s23 = mkInt(atoi(var));
      i = mkInstr(ADD,v3,s13,s23,t, index);
      return i;
      break;
      case 4:
      string = strdup(s);
      token = strsep(&string, "=");
      Elem v4 = mkVar(token);
      token = strsep(&string, "=");
      //token[strlen(token)-1] = '\0';
      var = strsep(&token, "+");
      Elem s14 = mkInt(atoi(var));
      var = strsep(&token, "+");
      Elem s24 = mkVar(var);
      i = mkInstr(ADD,v4,s14,s24,t, index);
      return i;
      break;
    }
    return i;
  }

  if(strstr(s, "-") != NULL){ //SUB
    int t = getType(s, "-");
    char *token, *string, *var;
    switch (t) {
      case 1:
      string = strdup(s);
      token = strsep(&string, "=");
      Elem v1 = mkVar(token);
      token = strsep(&string, "=");
      //token[strlen(token)-1] = '\0';
      var = strsep(&token, "-");
      Elem s11 = mkVar(var);
      var = strsep(&token, "-");
      Elem s21 = mkVar(var);
      i = mkInstr(SUB,v1,s11,s21,t, index);
      return i;
      break;
      case 2:
      string = strdup(s);
      token = strsep(&string, "=");
      Elem v2 = mkVar(token);
      token = strsep(&string, "=");
      //token[strlen(token)-1] = '\0';
      var = strsep(&token, "-");
      Elem s12 = mkInt(atoi(var));
      var = strsep(&token, "-");
      Elem s22 = mkInt(atoi(var));
      i = mkInstr(SUB,v2,s12,s22,t, index);
      return i;
      break;
      case 3:
      string = strdup(s);
      token = strsep(&string, "=");
      Elem v3 = mkVar(token);
      token = strsep(&string, "=");
      //token[strlen(token)-1] = '\0';
      var = strsep(&token, "-");
      Elem s13 = mkVar(var);
      var = strsep(&token, "-");
      Elem s23 = mkInt(atoi(var));
      i = mkInstr(SUB,v3,s13,s23,t, index);
      return i;
      break;
      case 4:
      string = strdup(s);
      token = strsep(&string, "=");
      Elem v4 = mkVar(token);
      token = strsep(&string, "=");
      //token[strlen(token)-1] = '\0';
      var = strsep(&token, "-");
      Elem s14 = mkInt(atoi(var));
      var = strsep(&token, "-");
      Elem s24 = mkVar(var);
      i = mkInstr(SUB,v4,s14,s24,t, index);
      return i;
      break;
    }
    return i;
  }

  if(strstr(s, "*") != NULL){ //MUL
    int t = getType(s, "*");
    char *token, *string, *var;
    switch (t) {
      case 1:
      string = strdup(s);
      token = strsep(&string, "=");
      Elem v1 = mkVar(token);
      token = strsep(&string, "=");
      //token[strlen(token)-1] = '\0';
      var = strsep(&token, "*");
      Elem s11 = mkVar(var);
      var = strsep(&token, "*");
      Elem s21 = mkVar(var);
      i = mkInstr(MUL,v1,s11,s21,t, index);
      return i;
      break;
      case 2:
      string = strdup(s);
      token = strsep(&string, "=");
      Elem v2 = mkVar(token);
      token = strsep(&string, "=");
      //token[strlen(token)-1] = '\0';
      var = strsep(&token, "*");
      Elem s12 = mkInt(atoi(var));
      var = strsep(&token, "*");
      Elem s22 = mkInt(atoi(var));
      i = mkInstr(MUL,v2,s12,s22,t, index);
      return i;
      break;
      case 3:
      string = strdup(s);
      token = strsep(&string, "=");
      Elem v3 = mkVar(token);
      token = strsep(&string, "=");
      //token[strlen(token)-1] = '\0';
      var = strsep(&token, "*");
      Elem s13 = mkVar(var);
      var = strsep(&token, "*");
      Elem s23 = mkInt(atoi(var));
      i = mkInstr(MUL,v3,s13,s23,t, index);
      return i;
      break;
      case 4:
      string = strdup(s);
      token = strsep(&string, "=");
      Elem v4 = mkVar(token);
      token = strsep(&string, "=");
      //token[strlen(token)-1] = '\0';
      var = strsep(&token, "*");
      Elem s14 = mkInt(atoi(var));
      var = strsep(&token, "+");
      Elem s24 = mkVar(var);
      i = mkInstr(MUL,v4,s14,s24,t, index);
      return i;
      break;
    }
    return i;
  }
  return i;
}

int getIndex(char* s, ILIST lista){
  while(lista != NULL){
    Instr i = head(lista);
    if(i.op == LABEL){
      if (strcmp(s, getName(i.first)) == 0) {
        return i.index;
      }
    }
    lista = lista->tail;
  }
  return 0;
}

// void exec(Instr i){
//   char* lab;
//   List* li;
//   int val, a1, a2;
//   switch(i.op){
//     case START:
//     break;
//     case PRINT:
//     li = lookup(getName(i.first));
//     val = getHashValue(li);
//     printf("%d ", val);
//     break;
//     case READ:
//     printf("Valor de %s = ", getName(i.first));
//     scanf("%d", &val);
//     insert(getName(i.first), val);
//     break;
//     case GOTO:
//     lab = getName(i.first);
//     break;
//     case ATRIB:
//     insert(getName(i.first), getVal(i.second));
//     break;
//     case ADD:
//     switch (i.type) {
//       case 1:
//       a1 = getHashValue(lookup(getName(i.second)));
//       a2 = getHashValue(lookup(getName(i.third)));
//       insert(getName(i.first), (a1 + a2));
//       break;
//       case 2:
//       insert(getName(i.first), (getVal(i.second) + getVal(i.third)));
//       break;
//       case 3:
//       a1 = getHashValue(lookup(getName(i.second)));
//       insert(getName(i.first), (a1 + getVal(i.third)));
//       break;
//       case 4:
//       a2 = getHashValue(lookup(getName(i.third)));
//       insert(getName(i.first), (a2 + getVal(i.second)));
//       break;
//     }
//   break;
//   case SUB:
//   switch (i.type) {
//     case 1:
//     a1 = getHashValue(lookup(getName(i.second)));
//     a2 = getHashValue(lookup(getName(i.third)));
//     insert(getName(i.first), (a1 - a2));
//     break;
//     case 2:
//     insert(getName(i.first), (getVal(i.second) - getVal(i.third)));
//     break;
//     case 3:
//     a1 = getHashValue(lookup(getName(i.second)));
//     insert(getName(i.first), (a1 - getVal(i.third)));
//     break;
//     case 4:
//     a2 = getHashValue(lookup(getName(i.third)));
//     insert(getName(i.first), (a2 - getVal(i.second)));
//     break;
//   }
//   break;
//   case MUL:
//   switch (i.type) {
//     case 1:
//     a1 = getHashValue(lookup(getName(i.second)));
//     a2 = getHashValue(lookup(getName(i.third)));
//     insert(getName(i.first), (a1 * a2));
//     break;
//     case 2:
//     insert(getName(i.first), (getVal(i.second) * getVal(i.third)));
//     break;
//     case 3:
//     a1 = getHashValue(lookup(getName(i.second)));
//     insert(getName(i.first), (a1 * getVal(i.third)));
//     break;
//     case 4:
//     a2 = getHashValue(lookup(getName(i.third)));
//     insert(getName(i.first), (a2 * getVal(i.second)));
//     break;
//   }
//   break;
//   }
// }
