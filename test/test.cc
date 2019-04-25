// TEST primitive parameter function call

#include <stdio.h>
#include <vector>

struct A {
  int a,b;
  A(){}
  A(int n){ a = n, b = -n, printf("int!\n"); }
  A(double d){ a = (int)d, b = -(int)d, printf("dub!\n"); }
  std::vector<int> operator,(const A& o){
    std::vector<int> v;
    v.push_back(this->a), v.push_back(o.a);
    return v;
  }
  bool operator()(){ return true; }
  int operator()(int n){ return n; }
  A operator+(const A& o){ return A(a + o.a); }
};

int main(){
  A a(6), b(7.0);
  printf("%d\n", a);
  std::vector<int> v((a,b));
  int i;
  for(i = 0; i < v.size(); ++i)
    printf("%d\n", v[i]);
  return 0;
}
