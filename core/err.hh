// ERR

#ifndef err_hh
#define err_hh

#include "def.hh"
#include "str.hh"


void kill(str s){
  printf("ERROR: %s\n", s.c_str());
  exit(1);
}


#endif
