#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//./main file.txt
int main(int argc, char const *argv[]) {
  init_table();
  char* buffer = NULL;
  size_t buffsize = 32;
  ssize_t aux;
  int i = 1;

  FILE *fp;
  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("FILE ERROR\n");
    return 0;
  }
  ILIST lista = mkList(mkInstr(START,empty(),empty(),empty(),0, 0),NULL);
  while ((aux = getline(&buffer, &buffsize, fp)) != -1) {
    removeSpaces(buffer);
    Instr inst = parseInstr(buffer, i);
    i++;
    lista = addLast(inst, lista);
  }

  fclose(fp);
  printf("Lista: \n");
  printList(lista);
  printf("----------------------\n");

  //Percorrer Lista
  while (lista != NULL) {
    Instr i = head(lista);
    Instr g;
    char* lab;
    List* li;
    int val, a1, a2;
    switch(i.op){
      case START:
      break;
      case QUIT:
      printf("\n");
      return 0;
      break;
      case PRINT:
      li = lookup(getName(i.first));
      val = getHashValue(li);
      printf("%d ", val);
      break;
      case READ:
      printf("Valor de %s = ", getName(i.first));
      scanf("%d", &val);
      insert(getName(i.first), val);
      break;
      case IF:
      li = lookup(getName(i.first));
      val = getHashValue(li);
      if (val == 0) {
        lista = lista->tail;
      }
      break;
      case GOTO:
      lab = getName(i.first);
      a1 = getIndex(lab, lista);
      lista = lista->tail;
      g = head(lista);
      while (a1 != g.index) {
        lista = lista->tail;
        g = head(lista);
      }
      break;
      case LABEL:
      break;
      case ATRIB:
      insert(getName(i.first), getVal(i.second));
      break;
      case ADD:
      switch (i.type) {
        case 1:
        a1 = getHashValue(lookup(getName(i.second)));
        a2 = getHashValue(lookup(getName(i.third)));
        insert(getName(i.first), (a1 + a2));
        break;
        case 2:
        insert(getName(i.first), (getVal(i.second) + getVal(i.third)));
        break;
        case 3:
        a1 = getHashValue(lookup(getName(i.second)));
        insert(getName(i.first), (a1 + getVal(i.third)));
        break;
        case 4:
        a2 = getHashValue(lookup(getName(i.third)));
        insert(getName(i.first), (a2 + getVal(i.second)));
        break;
      }
      break;
      case SUB:
      switch (i.type) {
        case 1:
        a1 = getHashValue(lookup(getName(i.second)));
        a2 = getHashValue(lookup(getName(i.third)));
        insert(getName(i.first), (a1 - a2));
        break;
        case 2:
        insert(getName(i.first), (getVal(i.second) - getVal(i.third)));
        break;
        case 3:
        a1 = getHashValue(lookup(getName(i.second)));
        insert(getName(i.first), (a1 - getVal(i.third)));
        break;
        case 4:
        a2 = getHashValue(lookup(getName(i.third)));
        insert(getName(i.first), (a2 - getVal(i.second)));
        break;
      }
      break;
      case MUL:
      switch (i.type) {
        case 1:
        a1 = getHashValue(lookup(getName(i.second)));
        a2 = getHashValue(lookup(getName(i.third)));
        insert(getName(i.first), (a1 * a2));
        break;
        case 2:
        insert(getName(i.first), (getVal(i.second) * getVal(i.third)));
        break;
        case 3:
        a1 = getHashValue(lookup(getName(i.second)));
        insert(getName(i.first), (a1 * getVal(i.third)));
        break;
        case 4:
        a2 = getHashValue(lookup(getName(i.third)));
        insert(getName(i.first), (a2 * getVal(i.second)));
        break;
      }
      break;
    }
    lista = lista->tail;
  }
  //Tipo 1 = str str
  //Tipo 2 = int int ok
  //Tipo 3 = str int ok
  //Tipo 4 = int str

  //TESTE TIPOS
  // char* s = "s = 1 + k;";
  // printf("%s\n", s);
  // removeSpaces(s);
  // printf("%s\n", s);
  // insert("a", 6);
  // printf("%u\n", hash("k"));
  // insert("p", 2);
  // printf("%u\n", hash("p"));
  // insert("s", 1);
  // printf("%u\n", hash("s"));
  // char* string = "k=s+p;";
  // Instr i = parseInstr(string);
  // if (i.tipo == 1) {
  //   int a1 = getHashValue(lookup(getName(i.second)));
  //   int a2 = getHashValue(lookup(getName(i.third)));
  //   printf("%d %d \n", a1, a2);
  //   insert(getName(i.first), (a1+a2));
  //   display();
  // }
  // char* s = "gotoL1";
  // char* string = strdup(s);
  // char* aux = strsep(&string, "o");
  // aux = strsep(&string, "o");
  // printf("%s\n", aux);

  // TESTE HASH
  // ILIST lista = mkList(mkInstr(START,empty(),empty(),empty()),NULL);
  // Instr i = mkInstr(PRINT,mkVar("x"),empty(),empty());
  // ILIST a = mkList(i, NULL);
  // lista = append(lista,a);
  // while (lista != NULL) {
  //   Instr aux = head(lista);
  //   escrever(aux);
  //   if(aux.op == PRINT){
  //     insert("ola",1);
  //     int val = getHashValue(lookup("ola"));
  //     printf("%d\n", val);
  //   }
  //   lista = lista->tail;
  // }
  // insert("ola", 69);
  // display();
  // List* n = lookup("ola");
  // int val = getHashValue(n);
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
