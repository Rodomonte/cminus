// NUM

#ifndef num_hh
#define num_hh

#include "flag.hh"


struct num : mem {
  flag negative;
  ll base;
  num* error;

  num(): negative(false), base(0) {}
  num(ll _base): negative(_base < 0), base(_base) {}
  num* clone(){ return this; } //!

  str _string(){
    return ""; //!
  }
  str serialize(){
    return ""; //!
  }
};


#endif
