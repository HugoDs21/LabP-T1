#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//./main file.txt
int main(int argc, char const *argv[]) {
  init_table();
  // char* buffer = NULL;
  // size_t buffsize = 32;
  // ssize_t aux;
  //
  // // FILE *fp;
  // // fp = fopen(argv[1], "r");
  // // if (fp == NULL) {
  // //   printf("FILE ERROR\n");
  // //   return 0;
  // // }
  // //
  // // while ((aux = getline(&buffer, &buffsize, fp)) != -1) {
  // //   removeSpaces(buffer);
  // //   printf("Line Lenth %zu: \n", aux-1); //aux - 1 para nao contar com o \n
  // //   printf("%s", buffer);
  // // }
  // //
  // // fclose(fp);

  //TESTE LISTAS
  // Instr i = mkInstr(ADD,mkVar("x"),mkInt(2),mkInt(3));
  // ILIST l = mkList(i,NULL);
  // printList(l);
  // Instr x = mkInstr(ATRIB,mkVar("y"),mkInt(3),empty());
  // ILIST l2 = addLast(x,l);
  // printList(l2);

  // //TESTE HASH
  // insert("x",2);
  // List* n = lookup("x");
  // int val = getHashValue(n);
  // printf("%d\n", val);
  // char* s = getHashKey(n);
  // printf("%s\n", s);
  // display();
  // return 0;

  //TESTE parseInstr
  char* s = "ler(k);";
  Instr plswork = parseInstr(s);
  escrever(plswork);
  // int v1, v2;
  // char* c;
  // // char c;
  // sscanf( s, "%c=%d+%d", &c, &v1, &v2 );
  // printf("%s %d %d\n", c, v1, v2);
  // printf("%d\n", var1);
  // printf("%d\n", var2);
  // char* a = "x=22+11;";
  // char* aux = malloc(sizeof(char));
  // strcpy(aux,a);
  // aux = strtok(aux, "=");
  // printf("%s\n", aux);
  // aux = strtok(NULL, "+");
  // printf("%s\n", aux);
  // aux = strtok(NULL, ";");
  // // printf("%s\n", aux);
  return 0;
}
