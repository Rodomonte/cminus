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

  llu& operator[](int i){ return block[i]; }
  llu at(int i) const { return block[i]; }
  char bit_at(int i) const {
    return (block[i>>6] & (1LLU << (63 - (i & 0x3F)))) ? 1 : 0;
  }
  void bit_set(int i, char b){
    if(!b && bit_at(i)) block[i>>6] ^= (1LLU << (63 - (i & 0x3F))); // on->off
    if(b && !bit_at(i)) block[i>>6] |= (1LLU << (63 - (i & 0x3F))); // off->on
  }

  bool operator==(const mem& o) const {
    if(size() != o.size()) return false;
    int i;
    for(i = 0; i < size(); ++i)
      if(block.at(i) != o.at(i)) return false;
    return true;
  }

  llu rev(llu n) const {
    int i,j;
    llu b,m,r;
    for(r = i = 0, b = (1LLU << 63), m = 1; i < 64; ++i, --j, b >>= 1, m <<= 1)
      if(n & m) r |= b;
    return r;
  }

  int space() const {
    int i;
    llu m;
    for(i = 0, m = 1; i < 64; ++i, m <<= 1)
      if(at(size()-1) & m) break;
    return i;
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
