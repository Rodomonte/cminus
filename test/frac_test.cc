// FRAC TEST

#include "../cminus.hh"


int main(){
  ASSERT = 0;
  printf("\nOperator Test:\n");

  printf("()\n");
  frac a(2);
  frac b(num(5));
  frac c(a);

  printf("==\n");
  assert(a == c);
  assert(a == 2);
  assert(b == num(5));

  return 0;
}
