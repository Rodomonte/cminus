// STAMP

#ifndef stamp_hh
#define stamp_hh

#include "type.hh"


struct stamp : type {
  llu clock;

  stamp(){}
  stamp(llu _clock): clock(_clock) {}

  virtual stamp* clone() const { cl_stamp.pb(*this); return &cl_stamp.back(); }

  //!
  virtual str _string() const { return ""; }
  virtual str serialize() const { return ""; }

  bool operator==(const stamp& o){ return clock == o.clock; }
  bool operator< (const stamp& o){ return clock < o.clock; }
  bool operator<=(const stamp& o){ return clock <= o.clock; }
  bool operator> (const stamp& o){ return clock > o.clock; }
  bool operator>=(const stamp& o){ return clock >= o.clock; }
};


#endif
