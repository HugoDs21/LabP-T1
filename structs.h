
typedef enum  {ATRIB, ADD, SUB, MUL, IF_I, PRINT, READ, GOTO_I, LABEL} OpKind;
typedef enum {INT_CONST, STRING, EMPTY} ElemKind;

typedef struct{
  ElemKind kind;
  union
  {
    int val;
    char* name;
  }content;
} Elem;

typedef struct{
  OpKind op;
  Elem first, second, third;
} Instr;

typedef struct list{
  Instr elem;
  struct list* next;
} ILIST;

Elem mkVar(char* s);
Elem mkInt(int x);
Elem empty();
Instr mkInstr(OpKind k, Elem x, Elem y, Elem z);
ILIST mkList(Instr head, ILIST tail);

int getVal(Elem x);
char* getName(Elem x);
void escrever(Instr inst);
