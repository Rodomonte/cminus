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

  //!
  virtual str _string(){ return ""; }
  virtual str serialize(){ return ""; }

  virtual stat _update(){ return stat(PASS); };
  virtual stat _update(stamp time){ return _update(); }
  virtual stat update(ll time) final {
    stamp ts(time);
    if(ts > last_upd){
      last_upd = ts;
      return _update(ts);
    }
    //! log to db
    return stat(PASS);
  }
  virtual stat update() final { return update(clock()); }

  virtual stat _validate(){};
  virtual stat validate() final {
    if(creation > last_upd || creation > last_vld || creation > last_act)
      return stat(KILL);
    return _validate();
  }
};


#endif
