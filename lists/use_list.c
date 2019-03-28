#include <stdio.h>

#include "list.h"

int quadrado(int x) {
   return x*x;
}

int par(int x) {
   return x%2==0;
}

int main(int argc, char const *argv[])
{
   LIST l1 = newlist(1, newlist(2, newlist(3, newlist(4, newlist(5, NULL)))));
   LIST l2 = newlist(4, newlist(4, newlist(30, newlist(2, NULL))));
   LIST l3 = append(l1, l2);
   LIST l4 = newlist(4, NULL);
   // printf("head of l1: %d\n", head(l1));
   // printf("size of l2: %d\n", size(l2));
   printlist(l4);


   return 0;
}
