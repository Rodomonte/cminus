// FRAC TEST

#include <stdio.h>

#include "../cminus.hh"


int main(){
  printf("\nOperator Test:\n");

  printf("()\n");
  frac a(-1);
  frac b(num(0));
  frac c(a);

  printf("=\n");
  a = 2;
  b = frac(5, 3);
  c = a;

  printf("==\n");
  assert(a == a);
  assert(a == 2);
  assert(a == frac(4, 2));
  assert(a == frac(-4, -2));
  assert(!(a == -2));
  assert(a == c);

  printf("!=\n");
  assert(!(a != a));
  assert(!(a != num(2)));
  assert(a != frac(2, 2));
  assert(a != frac(-2, 1));
  assert(a != b);
  assert(!(a != c));

  printf("<\n");
  assert(!(a < a));
  assert(b < 2);
  assert(b < a);
  assert(!(a < b));
  assert(!(a < c));
  assert(b < frac(2));

  printf(">\n");
  assert(!(a > a));
  assert(b > 1);
  assert(a > b);
  assert(!(b > a));
  assert(!(c > a));
  assert(b > frac(4, 3));

  printf("<=\n");
  assert(a <= a);
  assert(b <= 2);
  assert(!(a <= b));
  assert(a <= c);
  assert(b <= frac(5, 3));

  printf(">=\n");
  assert(a >= a);
  assert(b >= 1);
  assert(a >= b);
  assert(a >= c);
  assert(b >= frac(4, 3));

  printf("++()\n");
  assert(++a == 3);
  assert(++b == frac(8, 3));
  assert(++frac(-1) == 0);

  printf("()++\n");
  assert(a++ == 3);
  assert(a == 4);
  assert(frac(-1)++ == -1);

  printf("--()\n");
  assert(--a == 3);
  assert(--b == frac(5, 3));
  assert(--frac(0) == -1);

  printf("()--\n");
  assert(a-- == 3);
  assert(a == 2);
  assert(frac(0)-- == 0);

  printf("+\n");
  assert(frac(1, 3) + frac(2, 3) == 1);
  assert(frac(-1, 3) + frac(1, 3) == 0);
  assert(frac(-1, 3) + frac(-2, 3) == -1);

  printf("+=\n");
  assert((frac(1, 3) += frac(2, 3)) == 1);
  assert((frac(-1, 3) += frac(1, 3)) == 0);
  assert((frac(-1, 3) += frac(-2, 3)) == -1);

  printf("-\n");
  assert(frac(4, 3) - frac(1, 3) == 1);
  assert(frac(1, 3) - frac(1, 3) == 0);
  assert(frac(-1, 3) - frac(2, 3) == -1);

  printf("-=\n");
  assert((frac(1) -= frac(1, 3)) == frac(2, 3));
  assert((frac(1, 3) -= frac(1, 3)) == 0);
  assert((frac(-1, 3) -= frac(2, 3)) == -1);

  printf("*\n");
  assert(frac(2, 3) * frac(3, 4) == frac(1, 2));
  printf("%s\n", (frac(-2, 3) * frac(3, 4))._string().c_str());
  printf("%s\n", frac(-1, 2)._string().c_str());
  assert(frac(-2, 3) * frac(3, 4) == frac(-1, 2));
  assert(frac(-2, 3) * frac(-3, 4) == frac(1, 2));

  printf("*=\n");
  assert((frac(2, 3) *= frac(3, 4)) == frac(1, 2));
  assert((frac(-2, 3) *= frac(3, 4)) == frac(-1, 2));
  assert((frac(-2, 3) *= frac(-3, 4)) == frac(1, 2));

  printf("/\n");
  assert(frac(1, 2) / frac(2, 3) == frac(3, 4));

  printf("/=\n");
  assert((frac(1, 2) /= frac(2, 3)) == frac(3, 4));

  printf("%%\n");

  printf("%%=\n");

  printf("^\n");

  printf("^=\n");

  printf("<<\n");

  printf("<<=\n");

  printf(">>\n");

  printf(">>=\n");

  printf("floor\n");
  assert(frac(1, 2).floor() == 0);
  assert(frac(2, 2).floor() == 1);
  assert(frac(3, 2).floor() == 1);

  printf("ceil\n");

  return 0;
}
