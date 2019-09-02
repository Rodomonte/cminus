// NUM TEST

#include "../cminus.hh"


int main(){
  printf("\nOperator Test:\n\nSmall numbers\n");

  printf("()\n");
  num a(-1);
  num b(0);
  num c(1);
  num d(b);

  printf("=\n");
  a = b = 2;
  c = 4;
  d = -2;

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

  printf("++()\n");
  assert(++a == 3);
  assert(++num(-1) == 0);

  printf("()++\n");
  assert(a++ == 3);
  assert(a == 4);
  assert(num(-1)++ == -1);

  printf("--()\n");
  assert(--a == 3);
  assert(--num(0) == -1);

  printf("()--\n");
  assert(a-- == 3);
  assert(a == 2);
  assert(num(0)-- == 0);

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
  assert(a - d == 8);
  assert(d - a == -8);
  assert(d - d == 0);

  printf("-=\n");
  assert((a -= b) == b);
  assert((d -= a) == -6);

  printf("*\n");
  assert(a * b == c);
  assert(a * 0 == 0);
  assert(a * 1 == a);
  assert(a * -3 == d);
  assert(c * d == -24);

  printf("*=\n");
  assert((a *= b) == c);
  assert((d *= d) == 36);

  printf("/\n");
  assert(a / 1 == a);
  assert(a / 2 == b);
  assert(a / a == 1);
  assert(d / 9 == c);

  printf("/=\n");
  assert((a /= b) == b);
  assert((d /= 9) == c);

  printf("<<\n");
  assert((a << 1) == c);
  assert((a << 2) == (c << 1));

  printf("<<=\n");
  assert((a <<= 1) == c);
  assert((b <<= 2) == (c << 1));

  printf(">>\n");
  assert((a >> 1) == 2);
  assert((b >> 2) == 2);

  printf(">>=\n");
  assert((a >>= 1) == 2);
  assert((b >>= 2) == a);

  printf("&\n");
  assert((num(5) & 12) == 4);
  assert((num(1) & 4) == 0);

  printf("|\n");
  assert((num(1) | 4) == 5);
  assert((num(0) | 7) == 7);

  printf("XOR\n");
  assert(num(0).XOR(7) == 7);
  assert(num(3).XOR(6) == 5);

  printf("^\n");
  assert((num(5) ^ 0) == 1);
  assert((num(5) ^ 1) == 5);
  assert((num(5) ^ 3) == 125);

  printf("gcd\n");
  assert(num(12).gcd(num(18)) == 6);

  printf("lcm\n");
  assert(num(10).lcm(num(6)) == 30);

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
