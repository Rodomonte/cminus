// MATH TEST

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../cminus.hh"


int main(){
  int i;
  double x;
  for(i = 0; i < 10000000; ++i){
    x = (double)rand() / (rand()+1);
    assert(sin(x) == _sin(x));
    assert(cos(x) == _cos(x));
    assert(tan(x) == _tan(x));
    assert(asin(x) == _asin(x));
    assert(acos(x) == _acos(x));
    assert(atan(x) == _atan(x));
  }
  return 0;
}
