// STAT

#ifndef stat_hh
#define stat_hh

#include "type.hh"


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
  stat* clone(){
    MEM.pb(stat()); //!
    return &MEM.back();
  }

  str _string(){
    return ""; //!
  }
  str serialize(){
    return ""; //!
  }
};


#endif
