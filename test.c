#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int getType(char* str, char* ch){
  //TIPOS
  //Tipo 1 = str str
  //Tipo 2 = int int
  //Tipo 3 = str int
  //Tipo 4 = int str
  char *token, *string, *tofree,*var1, *var2, *dup1, *dup2;
  int tmp1,tmp2, tipo;
  tofree = string = strdup(str);
  if (string == NULL)
  return -1;

  token = strsep(&string, "=");
  token = strsep(&string, "=");
  token[strlen(token)-1]='\0'; // remove ";"
  dup1 = strdup(token);
  dup2 = strdup(token);

  var1 = strsep(&dup1, ch);
  if((var1[0] > 0x60 && var1[0] < 0x7B)) // detect string
  {
    var1 = strsep(&dup1, ch);
    if((var1[0] > 0x61 && var1[0] < 0x7A)){
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
  if(!(var2[0] > 0x60 && var2[0] < 0x7B)){
    tmp1 = atoi(var2);
    var2 = strsep(&dup2, ch);
    if(!(var2[0] > 0x61 && var2[0] < 0x7A)){
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
//
int main()
{
  char* s = "ler(k);";
  char* string = strdup(s);
  char* token = strsep(&string, "(");
  printf("%s\n", token);
  token = strsep(&string, ")");
  printf("%s\n", token);
  // token[strlen(token)-1]='\0';
  // char* var;
  // var = strsep(&token, "+");
  // printf("%s\n", var);
  // var = strsep(&token, "+");
  // printf("%s\n", var);
    //Tipo 1 = str str
    //Tipo 2 = int int
    //Tipo 3 = str int
    //Tipo 4 = int str

  return 0;
}
