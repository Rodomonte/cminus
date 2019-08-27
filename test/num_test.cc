// NUM TEST

#include <stdio.h>
#include <stdlib.h>
#include "../cminus.hh"

int main(){
  ASSERT = 0;
  printf("\nOperator Test:\n\nSmall numbers\n");

  printf("=\n");
  num a,b,c,d;
  a = b = 2;
  c = 4;
  d = -2;

  // 1-7
  printf("==\n");
  assert(a == 2);
  assert(!(a == 3));
  assert(a == a);
  assert(a == b);
  assert(!(a == c));
  assert(!(c == b));
  assert(!(a == d));

  // 8-14
  printf("!=\n");
  assert(!(a != 2));
  assert(a != 3);
  assert(!(a != a));
  assert(!(a != b));
  assert(a != c);
  assert(c != b);
  assert(a != d);

  // 15-21
  printf("<\n");
  assert(!(a < 2));
  assert(a < 3);
  assert(!(a < a));
  assert(!(a < b));
  assert(a < c);
  assert(!(c < b));
  assert(d < 0);

  // 22-28
  printf(">\n");
  assert(a > 1);
  assert(!(a > 2));
  assert(!(a > a));
  assert(!(a > b));
  assert(!(a > c));
  assert(c > b);
  assert(a > d);

  // 29-35
  printf("<=\n");
  assert(!(a <= 1));
  assert(a <= 2);
  assert(a <= a);
  assert(a <= b);
  assert(a <= c);
  assert(!(c <= b));
  assert(d <= 0);

  // 36-42
  printf(">=\n");
  assert(a >= 2);
  assert(!(a >= 3));
  assert(a >= a);
  assert(a >= b);
  assert(!(a >= c));
  assert(c >= b);
  assert(a >= d);

  // 43-48
  printf("+\n");
  assert(a + 0 == a);
  assert(a + 2 == c);
  assert(a + a == c);
  assert(a + b == c);
  assert(a + d == 0);
  assert(c + d == a);

  // 49-50
  printf("+=\n");
  assert((a += b) == c);
  assert((d += d) == -4);

  // 51-56
  printf("-\n");
  assert(a - 0 == a);
  assert(a - b == b);
  assert(c - c == 0);
  assert(a - d == 8);
  assert(d - a == -8);
  assert(d - d == 0);

  // 57-58
  printf("-=\n");
  assert((a -= b) == b);
  assert((d -= a) == -6);

  // 59-63
  printf("*\n");
  assert(a * b == c);
  assert(a * 0 == 0);
  assert(a * 1 == a);
  assert(a * -3 == d);
  assert(c * d == -24);

  // 64-65
  printf("*=\n");
  assert((a *= b) == c);
  assert((d *= d) == 36);

  // 66-69
  printf("/\n");
  assert(a / 1 == a);
  assert(a / 2 == b);
  assert(a / a == 1);
  assert(d / 9 == c);

  // 70-71
  printf("/=\n");
  assert((a /= b) == b);
  assert((d /= 9) == c);

  // 72-73
  printf("<<\n");
  assert((a << 1) == c);
  assert((a << 2) == (c << 1));

  // 74-75
  printf("<<=\n");
  assert((a <<= 1) == c);
  assert((b <<= 2) == (c << 1));

  // 76-77
  printf(">>\n");
  assert((a >> 1) == 2);
  assert((b >> 2) == 2);

  // 78-79
  printf(">>=\n");
  assert((a >>= 1) == 2);
  assert((b >>= 2) == a);

  // 80-81
  printf("&\n");
  assert((num(5) & 12) == 4);
  assert((num(1) & 4) == 0);

  // 82-83
  printf("|\n");
  assert((num(1) | 4) == 5);
  assert((num(0) | 7) == 7);

  // 84-85
  printf("XOR\n");
  assert(num(0).XOR(7) == 7);
  assert(num(3).XOR(6) == 5);

  // 86-88
  printf("^\n");
  assert((num(5) ^ 0) == 1);
  assert((num(5) ^ 1) == 5);
  assert((num(5) ^ 3) == 125);

  // 89-
  printf("Complex\n");
  assert((num(1) << 20) - 1 == num((1 << 20) - 1));


  printf("\nBig numbers\n");
  a = (1LLU << 62) + (1LLU << 20);
  b = (1LLU << 62);
  c = (num(1) << 124);
  d = (num(1) << 124) + (num(1) << 83) + (num(1) << 40);

  printf("*\n");
  assert(a * a == d);
  assert(b * b == c);

  printf("/\n");
  assert(d / a == a);
  assert(c / b == b);

  return 0;
}