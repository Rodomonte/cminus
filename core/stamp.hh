// STAMP

#ifndef stamp_hh
#define stamp_hh

#include "type.hh"


struct stamp : type {
  ll clock;

  stamp(){}
  stamp(ll _clock): clock(_clock) {}

  virtual stamp* clone(){ cl_stamp.pb(*this); return &cl_stamp.back(); }

  //!
  virtual str _string(){ return ""; }
  virtual str serialize(){ return ""; }

  bool operator==(const stamp& o){ return clock == o.clock; }
  bool operator< (const stamp& o){ return clock < o.clock; }
  bool operator<=(const stamp& o){ return clock <= o.clock; }
  bool operator> (const stamp& o){ return clock > o.clock; }
  bool operator>=(const stamp& o){ return clock >= o.clock; }
};


#endif
