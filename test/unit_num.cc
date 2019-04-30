// NUM UNIT TEST

#include <stdio.h>
#include <stdlib.h>
#include "../cminus.hh"

//! neg
int main(){
  num a,b,c;

  ASSERT = 0;
  printf("Operator Test:\n");

  printf("=\n");
  a = b = 2;
  c = 4;

  printf("string: %s %s %s\n",
         a.string().c_str(), b.string().c_str(), c.string().c_str());

  printf("==\n");
  assert(a == 2);
  assert(!(a == 3));
  assert(a == a);
  assert(a == b);
  assert(!(a == c));
  assert(!(c == b));

  printf("!=\n");
  assert(!(a != 2));
  assert(a != 3);
  assert(!(a != a));
  assert(!(a != b));
  assert(a != c);
  assert(c != b);

  printf("<\n");
  assert(!(a < 2));
  assert(a < 3);
  assert(!(a < a));
  assert(!(a < b));
  assert(a < c);
  assert(!(c < b));

  printf(">\n");
  assert(a > 1);
  assert(!(a > 2));
  assert(!(a > a));
  assert(!(a > b));
  assert(!(a > c));
  assert(c > b);

  printf("<=\n");
  assert(!(a <= 1));
  assert(a <= 2);
  assert(a <= a);
  assert(a <= b);
  assert(a <= c);
  assert(!(c <= b));

  printf(">=\n");
  assert(a >= 2);
  assert(!(a >= 3));
  assert(a >= a);
  assert(a >= b);
  assert(!(a >= c));
  assert(c >= b);

  printf("+\n");
  assert(a + 0 == a);
  assert(a + 2 == c);
  assert(a + a == c);
  assert(a + b == c);

  printf("+=\n");
  assert((a += b) == c);
  assert((b += b) == a);

  return 0;
}
