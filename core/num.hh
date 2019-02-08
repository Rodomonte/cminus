// NUM

#ifndef num_hh
#define num_hh

#include "flag.hh"


struct num : mem {
  flag negative;
  num* error;

  num(): negative(false), error(NULL){ block.pb(0); }
  num(ll _base): negative(_base < 0), error(NULL){ block.pb(_base); }

  num& asn(const num& o){
    negative = o.negative;
    if(o.error)
      cl_num.pb(*(o.error));
    block = o.block;
    return *this;
  }

  num* clone(){
    cl_num.pb(num());
    return &cl_num.back().asn(*this);
  }

  num& operator=(const num& o){
    asn(o);
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
