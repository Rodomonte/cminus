// THING

#ifndef thing_hh
#define thing_hh

#include "time.hh"


// Timestamped object core
struct Thing { // ABSTRACT
  time creation, last_upd, last_val, last_act;
  Thing(){
    creation = last_upd = clock();
    //universe.insert(this);
  }
  virtual Thing* clone() const = 0;

  virtual void _upd(){};
  virtual void _upd(ll time){ _upd(); }
  virtual void upd(ll time) final {
    if(time > last_upd) last_upd = time, _upd(time);
  }
  virtual void upd() final { upd(clock()); }

  virtual str _to_str() = 0;
  virtual str to_str() final { //! test proper type
    return str(typeid(*this).name()) + ": " + _to_str();
  }
};


#endif
