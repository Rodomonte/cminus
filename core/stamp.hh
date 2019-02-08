// STAMP

#ifndef stamp_hh
#define stamp_hh

#include "type.hh"


struct stamp : type {
  ll clock;

  stamp(){}
  stamp(ll _clock): clock(_clock) {}
  stamp clone(){ return stamp(); }

  bool operator==(const stamp& o){ return clock == o.clock; }
  bool operator< (const stamp& o){ return clock < o.clock; }
  bool operator<=(const stamp& o){ return clock <= o.clock; }
  bool operator> (const stamp& o){ return clock > o.clock; }
  bool operator>=(const stamp& o){ return clock >= o.clock; }

  str _string(){
    return ""; //!
  }
  str serialize(){
    return ""; //!
  }
};


#endif