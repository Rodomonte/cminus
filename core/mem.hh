// MEM

#ifndef mem_hh
#define mem_hh

#include "type.hh"


struct mem : type {
  vec<llu> block; //! vec/list/array/stack/deque/map?

  mem(){}

  mem* clone(){ cl_mem.pb(*this); return &cl_mem.back(); }

  bool operator==(const mem& o){
    if(block.size() != o.block.size()) return false;
    int i;
    for(i = 0; i < block.size(); ++i)
      if(block[i] != o.block[i]) return false;
    return true;
  }

  void extend(int n){
    int i;
    for(i = 0; i < n; ++i)
      block.pb(0);
  }

  str _string(){
    return ""; //!
  }

  str serialize(){
    return ""; //!
  }
};


#endif
