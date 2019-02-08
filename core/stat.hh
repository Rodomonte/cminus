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

  stat* clone(){ cl_stat.pb(*this); return &cl_stat.back(); }

  str _string(){
    return ""; //!
  }

  str serialize(){
    return ""; //!
  }
};


#endif
