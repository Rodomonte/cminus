// MEM

#ifndef mem_hh
#define mem_hh

#include "type.hh"


struct mem : type {
  vec<llu> block; //! vec/list/array/stack/deque/map?

  mem(){ block.pb(0); }

  virtual mem* clone() const { cl_mem.pb(*this); return &cl_mem.back(); }
  virtual int size() const { return block.size(); }
  virtual void clear(){ block.clear(), block.pb(0); }

  //!
  virtual str _string() const { return ""; }
  virtual str serialize() const { return ""; }

  llu at(int i) const { return block[i]; }
  llu& operator[](int i){ return block[i]; }

  bool operator==(const mem& o) const {
    if(size() != o.size()) return false;
    int i;
    for(i = 0; i < size(); ++i)
      if(block.at(i) != o.at(i)) return false;
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
  }
  void extend(){ resize(size() + 1); }
};


#endif
