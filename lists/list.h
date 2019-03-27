typedef struct list
{
   int head;
   struct list *tail;
} *LIST;

LIST newlist(int, LIST);
int head(LIST);
LIST tail(LIST);
int size(LIST);
LIST append(LIST, LIST);
int nth(LIST, int);
LIST map(int (*f)(int), LIST l);
LIST filter(int (*p)(int), LIST l);
//LIST filter(bool (*p)(int), LIST l);
void printlist(LIST);
