// MEM

#ifndef mem_hh
#define mem_hh

#include "type.hh"


struct mem : type {
  bool stable;
  vec<llu> block; //! vec/list/array/stack/deque/map?

  mem(): stable(true) { block.pb(0); }

  virtual mem* clone(){ cl_mem.pb(*this); return &cl_mem.back(); }
  virtual int size(){ return block.size(); }
  virtual void clear(){ block.clear(), block.pb(0), stable = true; }

  llu& operator[](int i){ return block[i]; }
  bool operator==(const mem& o){
    if(size() != o.size()) return false;
    int i;
    for(i = 0; i < size(); ++i)
      if(block[i] != o[i]) return false;
    return true;
  }

  void resize(int n){
    int i;
    if(n < size() - n){
      block.clear();
      for(i = 0; i < n; ++i)
        block.pb(0);
    }
    for(; size() > n; block.pop_back());
    for(; size() < n; block.pb(0));
    stable = false;
  }

  //!
  virtual str _string(){ return ""; }
  virtual str serialize(){ return ""; }
};


#endif
