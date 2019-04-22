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


int getType(char* str, char* ch){
  //TIPOS
  //Tipo 1 = str str
  //Tipo 2 = int int
  //Tipo 3 = str int
  //Tipo 4 = int str
  char *token, *string, *var1, *var2, *dup1, *dup2;
  int tipo;
  string = strdup(str);
  if (string == NULL)
  return -1;

  token = strsep(&string, "=");
  token = strsep(&string, "=");
  dup1 = strdup(token);
  dup2 = strdup(token);

  var1 = strsep(&dup1, ch);
  if((var1[0] >= 97 && var1[0] <= 123) || (var1[0] >= 65 && var1[0] <= 90)) // detect string
  {
    var1 = strsep(&dup1, ch);
    if((var1[0] >= 97 && var1[0] <= 123) || (var1[0] >= 65 && var1[0] <= 90)){
      tipo = 1;
      return tipo;
    }
    else {
      tipo = 3;
      return tipo;
    }
  }

  var2 = strsep(&dup2, ch);
  if(!((var2[0] >= 97 && var2[0] <= 123) || (var2[0] >= 65 && var2[0] <= 90))){
    var2 = strsep(&dup2, ch);
    if(!((var2[0] >= 97 && var2[0] <= 123) || (var2[0] >= 65 && var2[0] <= 90))){
      tipo = 2;
      return tipo;
    }
    else {
      tipo = 4;
      return tipo;
    }
  }
  return 0;
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
  int i = 0;
  for (i; str[i]; i++)
  if (str[i] != ' ')
  str[count++] = str[i];
  str[count] = '\0';
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
