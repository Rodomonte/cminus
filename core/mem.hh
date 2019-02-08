// MEM

#ifndef mem_hh
#define mem_hh

#include "type.hh"


struct mem : type {
  vec<ll> block;

  mem(){}

  mem* clone(){ cl_mem.pb(*this); return &cl_mem.back(); }

  str _string(){
    return ""; //!
  }

  str serialize(){
    return ""; //!
  }
};


#endif
