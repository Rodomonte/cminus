// STAT

#ifndef stat_hh
#define stat_hh

#include "type.hh"


//! Perhaps no enum, instead global static stats
enum CODE {
  PASS
, KILL
, BREAK
, CONTINUE
};

struct stat : type {
  CODE code;

  stat(){}
  stat(CODE _code): code(_code) {}

  virtual stat* clone(){ cl_stat.pb(*this); return &cl_stat.back(); }

  //!
  virtual str _string(){ return ""; }
  virtual str serialize(){ return ""; }
};


#endif
