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
  ILIST lista = mkList(mkInstr(START,empty(),empty(),empty()),NULL);
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
  ILIST a = mkList(mkInstr(PRINT,mkVar("x"),empty(),empty()), NULL);
  lista = append(lista, a);
  //Percorrer Lista
  List* l;
  int val;
  char* s;
  while (lista != NULL) {
    Instr i = head(lista);
    switch (i.op) {
      // case START:
      // break;
      // case READ:
      // printf("Valor de %s = ", getName(i.first));
      // scanf("%d", &val);
      // insert(getName(i.first), val);
      // display();
      // break;
      case PRINT:
      printf("ENTREI NO PRINT\n");
      printf("%s\n", getName(i.first));
      l = lookup(getName(i.first));
      printf("CONSEGUI DAR LOOKUP\n");
      val = getHashValue(l);
      printf("%d\n", val);
      break;
      // case ATRIB:
      // insert(getName(i.first), getVal(i.second));
      // break;
    }
    lista = lista->tail;
  }


  //TESTE EXEC
  // char* string = "escrever(k);";
  // Instr i = parseInstr(string);
  // escrever(i);
  // insert(getName(i.first), 6);
  // display();
  // List* n = lookup("k");
  // int val = getHashValue(n);
  // printf("%d\n", val);

  // TESTE HASH
  // Instr i = mkInstr(ATRIB,mkVar("x"),mkInt(2),empty());
  // insert(getName(i.first),2);
  // display();
  // List* n = lookup(getName(i.first));
  // int val = getHashValue(n);
  // printf("%d\n", val);
  // printf("%d\n", val);
  // char* s = getHashKey(n);
  // printf("%s\n", s);
  // //display();
  // insert("x", 5);
  // display();
  // char* string = "escrever(k)";
  // Instr i = parseInstr(string);
  // printf("%s\n", getName(i.first));
  // insert(getName(i.first), 2);
  // display();
  // // List* a = lookup(getName(i.first));
  // char* s2 = getHashKey(lookup(getName(i.first)));
  // printf("%s\n", s2);
  // int v = getHashValue(lookup(getName(i.first)));
  // printf("%d\n", v);

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
