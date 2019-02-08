// FLAG

#ifndef flag_hh
#define flag_hh

#include "mem.hh"


struct flag : type {
  static mem registry;

  flag(){} //!
  flag(bool _val){} //!

  flag* clone(){ cl_flag.pb(*this); return &cl_flag.back(); } //!

  flag& operator=(const flag& o){ //!
    return *this;
  }

  str _string(){
    return ""; //!
  }
  str serialize(){
    return ""; //!
  }
};


#endif
