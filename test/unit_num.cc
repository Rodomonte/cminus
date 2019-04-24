// NUM UNIT TEST

#include "stdio.h"
#include "stdlib.h"
#include "../core/num.hh"

bool assert(bool b){ if(!b){ printf("Assertion failed.\n"); exit(1); } }

int main(){
  num a,b,c;

  a = b = 0;
  assert(a == 0);
  assert(a == b);

  return 0;
}
