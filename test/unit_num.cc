// NUM UNIT TEST

#include <stdio.h>
#include <stdlib.h>
#include "../cminus.hh"

int main(){
  num a,b,c;

  printf("assign\n");
  a = b = 2, c = 4;

  str s(a.string()), t(b.string()), u(c.string());
  printf("%s %s %s\n", s.c_str(), t.c_str(), u.c_str());

  printf("compare\n");
  assert(a == 2);
  assert(a == b);
  assert(a != c);
  assert(c != 2);

  printf("add\n");
  assert(a + b == 4);
  assert(a + b == c);

  printf("addeq\n");
  assert((a += b) == c);
  assert((b += b) == a);

  return 0;
}
