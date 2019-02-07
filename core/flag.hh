// FLAG

#ifndef flag_hh
#define flag_hh

#include "mem.hh"


struct flag : type {
  static mem registry;

  flag(){}
  flag(bool _val){} //!
  flag* clone(){ return this; } //!

  str _string(){
    return ""; //!
  }
  str serialize(){
    return ""; //!
  }
};


#endif
