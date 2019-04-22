#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list{
   Instr head;
   struct list *tail;
} *ILIST;

ILIST mkList(Instr, ILIST);
Instr head(ILIST);
ILIST tail(ILIST);
void printList(ILIST);
ILIST append(ILIST, ILIST);
ILIST addLast(Instr, ILIST);
int getIndex(char*, ILIST);
