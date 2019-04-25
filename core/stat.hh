// STAT

#ifndef stat_hh
#define stat_hh

#include "type.hh"
#include "stamp.hh"


enum CODE {
  PASS
, KILL
};

struct stat : type {
  CODE code;
  stamp time;

  stat(): time(clock()) {}
  stat(CODE _code): stat() { code = _code; }

  virtual stat* clone() const { cl_stat.pb(*this); return &cl_stat.back(); }

  //!
  virtual str _string() const { return ""; }
  virtual str serialize() const { return ""; }
};


#endif
