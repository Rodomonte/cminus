// UTIL

#ifndef util_hh
#define util_hh

#include "incl.hh"


#define llu unsigned long long
#define uset std::unordered_set
#define umap std::unordered_map
#define iter iterator

#define INT_MIN -2147483647
#define INT_MAX 2147483647
#define LLU_MAX 18446744073709551615LLU
#define DBL_MIN -1.79769e+308
#define DBL_MAX 1.79769e+308


char buf[10485760];


#define kill(e) \
  printf("ERR in %s:%s: %s\n", __FILE__, __FUNCTION__, e); exit(1);
#define assert(b) if(!b) kill("Assertion failed");

void call(const char* cmd){
  int r = system(cmd);
  assert(WIFEXITED(r) && !WEXITSTATUS(r));
}


#endif
