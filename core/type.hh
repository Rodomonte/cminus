// TYPE

#ifndef type_hh
#define type_hh

#include "glb.hh"
#include "str.hh"


struct type { // ABSTRACT
  virtual type* clone() const = 0; //? type&
  virtual str _string() const = 0;
  virtual str string() const final {
    return str(typeid(*this).name()) + ": " + _string(); //!
  }
  virtual str serialize() const = 0;
  virtual int size() const { return 1; }
  virtual void clear(){}
};


#endif
