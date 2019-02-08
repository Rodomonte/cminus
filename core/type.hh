// TYPE

#ifndef type_hh
#define type_hh

#include "glb.hh"
#include "str.hh"


struct type { // ABSTRACT
  virtual type clone() = 0;
  virtual str _string() = 0;
  virtual str string() final {
    return str(typeid(*this).name()) + ": " + _string(); //!
  }
  virtual str serialize() = 0;
};


#endif
