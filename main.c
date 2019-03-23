#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  Elem var1 = mkVar("x");
  Elem var2 = mkInt(1);
  Elem var3 = empty();
  Instr inst1 = mkInstr(ATRIB,var1,var2,var3);
  escrever(inst1);
  Elem var4 = mkVar("y");
  Elem var5 = mkInt(2);
  Instr inst2 = mkInstr(ADD,var4,var1,var5);
  escrever(inst2);
  Elem var6 = mkVar("z");
  Instr inst3 = mkInstr(SUB,var6,var4,var1);
  escrever(inst3);
  return 0;
}
