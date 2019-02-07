// THING

#ifndef thing_hh
#define thing_hh

#include "time.hh"
#include "num.hh"
#include "str.hh"
#include "../db/db.hh"


// Timestamped object core
struct Thing : type { // ABSTRACT
  stamp creation, last_upd, last_vld, last_act;

  Thing(){
    creation = last_upd = clock();
  }

  virtual void _upd(){};
  virtual void _upd(stamp time){ _upd(); }
  virtual void upd(ll time) final {
    stamp ts(time);
    if(ts > last_upd) last_upd = ts, _upd(ts);
    //! log to db
  }
  virtual void upd() final { upd(clock()); }

  num hash(){
    return num(creation.clock);
  };
};


#endif
