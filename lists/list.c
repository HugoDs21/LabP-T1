#include <stdio.h>
#include <stdlib.h>

#include "list.h"

LIST newlist(int n, LIST l1) {
   LIST l = malloc(sizeof(struct list));
   l->head = n;
   l->tail = l1;
   return l;
}

int head(LIST l) {
   return l->head;
}

LIST tail(LIST l) {
   return l->tail;
}

int size(LIST l) {
   int sum = 0;
   while(l != NULL) {
      l = l->tail;
      sum++;
   }
   return sum;
}

int nth(LIST l, int p) {
   int i;
   for (i = 0; i + 1 < p; ++i)
      l=l->tail;
   return l->head;
}

LIST append(LIST l1, LIST l2) {
   LIST l = newlist(l1->head, NULL);
   LIST temp;
   LIST curr = l;
   l1 = l1->tail;
   while (l1 != NULL) {
      temp = newlist(l1->head, NULL);
      curr->tail = temp;
      curr = curr->tail;
      l1 = l1->tail;
   }
   while (l2 != NULL) {
      temp = newlist(l2->head, NULL);
      curr->tail = temp;
      curr = curr->tail;
      l2 = l2->tail;
   }
   return l;
}

LIST map(int (*f)(int), LIST l) {
   int x;
   LIST r;

   if (l == NULL) {
      return NULL;
   } else {
      x = head(l);
      r = tail(l);
      return newlist(f(x), map(f,r));
   }
}

LIST filter(int (*f)(int), LIST l) {
   int x;
   LIST r;

   if (l == NULL) {
      return NULL;
   } else {
      x = head(l);
      r = tail(l);
      if (f(x))
         return newlist(x, filter(f, r));
      else
         return filter(f,r);
   }
}

void printlist(LIST l) {
   while(l != NULL) {
      printf("%d ", l->head);
      l = l->tail;
   }
   printf("\n");
}