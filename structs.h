typedef enum  {ATRIB, ADD, SUB, MUL, IF_I, PRINT, READ, GOTO_I, LABEL} OpKind;

typedef enum {EMPTY, INT_CONST, STRING} ElemKind;

typedef struct{
  ElemKind kind;
  union
  {
    int val;
    char* name;
  } contents;
} Elem;

typedef struct{
  OpKind op;
  Elem first, second, third;
} Instr;

typedef struct{
  Instr elem;
  struct list *next;
} *ILIST;

Elem mkVar(char* s);
Elem mkVar(int x);
Instr mkInstr(OpKind k, Elem x, Elem y, Elem z);
ILIST mkList(Instr head, ILIST tail);
