// THING

#ifndef thing_hh
#define thing_hh

#include "stat.hh"
#include "stamp.hh"
#include "num.hh"
#include "str.hh"
#include "../db/db.hh"


// Timestamped object core
struct Thing : type { // ABSTRACT
  stamp creation, last_upd, last_vld, last_act;

  Thing(){
    creation = last_upd = clock();
  }

  virtual Thing* clone(){ cl_thing.pb(*this); return &cl_thing.back(); }

  virtual stat _upd(){ return stat(PASS); };
  virtual stat _upd(stamp time){ return _upd(); }
  virtual stat upd(ll time) final {
    stamp ts(time);
    if(ts > last_upd){
      last_upd = ts;
      return _upd(ts);
    }
    //! log to db
    return stat(PASS);
  }
  virtual stat upd() final { return upd(clock()); }

  virtual stat _validate(){};
  virtual stat validate() final {
    if(creation > last_upd || creation > last_vld || creation > last_act)
      return stat(KILL);
    return _validate();
  }

  //!
  virtual str _string(){ return ""; }
  virtual str serialize(){ return ""; }
};


#endif
