#ifndef __GUARD_LISTS__
#define __GUARD_LISTS__

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
void execlist(ILIST);

#endif
