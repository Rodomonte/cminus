// MEM

#ifndef mem_hh
#define mem_hh

#include "type.hh"


struct mem : type {
  vec<char> block;

  mem(){}
  mem* clone(){ return this; } //!

  str _string(){
    return ""; //!
  }
  str serialize(){
    return ""; //!
  }
};


#endif
