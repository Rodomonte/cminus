// FRAC

#ifndef frac_hh
#define frac_hh

#include "num.hh"


struct frac : num {
  num den;

  frac(): num(), den(1) {}
  frac(ll _num): frac(_num, 1) {}
  frac(const num& _num): frac(_num, num(1)) {}
  frac(ll _num, ll _den): frac(num(_num), num(_den)) {}
  frac(const num& _num, const num& _den): den(_den) { num::operator=(_num); }

  virtual frac* clone() const { cl_frac.pb(*this); return &cl_frac.back(); }
  virtual str serialize() const { return ""; } //!

  virtual double _double() const { return (double)_int() / den._int(); }
  virtual str _string() const { return num::_string() + "/" + den._string(); }
};


#endif
