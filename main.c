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
  // FILE *fp;
  // fp = fopen(argv[1], "r");
  // if (fp == NULL) {
  //   printf("FILE ERROR\n");
  //   return 0;
  // }
  // ILIST lista = mkList(mkInstr(START,empty(),empty(),empty()),NULL);
  // while ((aux = getline(&buffer, &buffsize, fp)) != -1) {
  //   removeSpaces(buffer);
  //   //printf("Line Lenth %zu: \n", aux-1); //aux - 1 para nao contar com o \n
  //   printf("Original = %s", buffer);
  //   Instr plswork = parseInstr(buffer);
  //   ILIST a = mkList(plswork, NULL);
  //   lista = append(lista, a);
  // }
  //
  // fclose(fp);
  // printf("Lista \n");
  // printList(lista);
  //
  //TESTE EXEC
  // char* string = "p = 2 + 4;";
  // Instr i = mkInstr(ADD,mkVar("p"), mkInt(2), mkInt(4));
  // escrever(i);
  // int sum = getVal(i.second) + getVal(i.third);
  // printf("%d + %d = %d\n", getVal(i.second), getVal(i.third), sum);
  // char* nome = getName(i.first);
  // printf("%s\n", nome);
  // removeSpaces(nome);
  // printf("%s\n", nome);
  // insert(nome,sum);
  // display();
  // List* n = lookup("p");
  // int val = getHashValue(n);

  // TESTE HASH
  // insert("x",2);
  // List* n = lookup("x");
  // int val = getHashValue(n);
  // printf("%d\n", val);
  // char* s = getHashKey(n);
  // printf("%s\n", s);
  // display();
  char* string = "p=2+5;";
  Instr i = parseInstr(string);
  int sum = getVal(i.second) + getVal(i.third);
  insert(getName(i.first), sum);
  display();
  // List* a = lookup(getName(i.first));
  char* s2 = getHashKey(lookup(getName(i.first)));
  printf("%s\n", s2);
  int v = getHashValue(lookup(getName(i.first)));
  printf("%d\n", v);

  //TESTE LISTAS
  // ILIST lista = mkList(mkInstr(START,empty(),empty(),empty()), NULL);
  // char* s = "ler(k);";
  // Instr i = parseInstr(s);
  // //escrever(i);
  // ILIST aux = mkList(i, NULL);
  // lista = append(lista,aux);
  // printList(lista);


  //TESTE parseInstr
  // char* s = "ler(k);";
  // Instr plswork = parseInstr(s);
  // escrever(plswork);
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
