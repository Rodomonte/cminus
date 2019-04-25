// NUM UNIT TEST

#include <stdio.h>
#include <stdlib.h>
#include "../cminus.hh"

int main(){
  num a,b,c;

  a = b = 0;
  assert(a == 0);
  assert(a == b);

  a = b = 2;
  assert(a + b == 4);

  return 0;
}
