// FRAC TEST

#include "../cminus.hh"


int main(){
  printf("\nOperator Test:\n");

  printf("()\n");
  frac a(-1);
  frac b(num(0));
  frac c(a);

  printf("=\n");
  a = 2;
  c = a;
  b = frac(5, 3);

  printf("==\n");
  assert(a == a);
  assert(a == c);
  assert(!(a == b));
  assert(a == 2);
  assert(!(b == 5));
  assert(b == frac(5, 3));
  assert(b == frac(10, 6));

  printf("!=\n");
  assert(!(a != a));
  assert(a != num(1));
  assert(a != b);
  assert(!(a != c));
  assert(b != 5);
  assert(!(b != frac(10, 6)));

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

  printf("+=\n");
  assert((frac(1, 3) += frac(2, 3)) == 1);

  printf("-\n");

  printf("-=\n");
  assert((frac(1) -= frac(1, 3)) == frac(2, 3));

  printf("*\n");

  printf("*=\n");
  assert((frac(2, 3) *= frac(3, 4)) == frac(1, 2));

  printf("/\n");

  printf("/=\n");
  assert((frac(1, 2) /= frac(2, 3)) == frac(3, 4));

  printf("%%\n");

  printf("%%=\n");

  printf("<<\n");

  printf("<<=\n");

  printf(">>\n");

  printf(">>=\n");

  return 0;
}
