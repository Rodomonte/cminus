// NUM UNIT TEST

#include <stdio.h>
#include <stdlib.h>
#include "../cminus.hh"

//! neg
int main(){
  num a,b,c,d;

  ASSERT = 0;
  printf("Operator Test:\n");

  printf("=\n");
  a = b = 2;
  c = 4;
  d = -2;

  // printf("string: %s %s %s\n",
  //        a.string().c_str(), b.string().c_str(), c.string().c_str());

  printf("==\n");
  assert(a == 2);
  assert(!(a == 3));
  assert(a == a);
  assert(a == b);
  assert(!(a == c));
  assert(!(c == b));
  assert(!(a == d));

  printf("!=\n");
  assert(!(a != 2));
  assert(a != 3);
  assert(!(a != a));
  assert(!(a != b));
  assert(a != c);
  assert(c != b);
  assert(a != d);

  printf("<\n");
  assert(!(a < 2));
  assert(a < 3);
  assert(!(a < a));
  assert(!(a < b));
  assert(a < c);
  assert(!(c < b));
  assert(d < 0);

  printf(">\n");
  assert(a > 1);
  assert(!(a > 2));
  assert(!(a > a));
  assert(!(a > b));
  assert(!(a > c));
  assert(c > b);
  assert(a > d);

  printf("<=\n");
  assert(!(a <= 1));
  assert(a <= 2);
  assert(a <= a);
  assert(a <= b);
  assert(a <= c);
  assert(!(c <= b));
  assert(d <= 0);

  printf(">=\n");
  assert(a >= 2);
  assert(!(a >= 3));
  assert(a >= a);
  assert(a >= b);
  assert(!(a >= c));
  assert(c >= b);
  assert(a >= d);

  printf("+\n");
  assert(a + 0 == a);
  assert(a + 2 == c);
  assert(a + a == c);
  assert(a + b == c);
  assert(a + d == 0);
  assert(c + d == a);

  printf("+=\n");
  assert((a += b) == c);
  assert((d += d) == -4);

  printf("-\n");
  assert(a - 0 == a);
  assert(a - b == b);
  assert(c - c == 0);
  assert(a - d == c);
  assert(d - a == -4);
  assert(d - d == 0);

  printf("-=\n");
  assert((a -= b) == b);
  assert((d -= a) == -6);

  return 0;
}
