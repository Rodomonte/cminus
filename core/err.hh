// ERR

#ifndef err_hh
#define err_hh

#include "def.hh"
#include "str.hh"

#define ERR kill("Banned keyword used");


void kill(str s){
  printf("ERROR: %s\n", s.c_str());
  exit(1);
}


#endif
