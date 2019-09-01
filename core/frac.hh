// FRAC

#ifndef frac_hh
#define frac_hh

#include "num.hh"


struct frac : num {
  num den;

  //! num _num, ll _den? etc
  frac(){ *this = 0; }
  frac(ll _num){ *this = _num; }
  frac(const num& _num){ *this = _num; }
  frac(ll _num, ll _den): frac(num(_num), num(_den)) {}
  frac(const num& _num, const num& _den): den(_den) { num::operator=(_num); }
  frac(const frac& _frac){ *this = _frac; }

  virtual frac* clone() const { cl_frac.pb(*this); return &cl_frac.back(); }
  virtual str serialize() const { return ""; } //!

  virtual double _double() const { return (double)_int() / den._int(); }
  virtual str _string() const { return num::_string() + "/" + den._string(); }

  void reduce(){
    num g = gcd(den);
    num::operator/=(g);
    den /= g;
  }

  frac& operator=(const frac& o){ num::operator=(o), den = o.den; }
  bool operator()() const { return *this != 0; }
  bool operator==(const frac& o) const {
    return num::operator==(o) && den == o.den;
  }
  bool operator!=(const frac& o) const { return !(*this == o); }

  // Num operand

  frac& operator=(const num& n){ num::operator=(n), den = 1; }
  bool operator==(const num& n) const { return num::operator==(n) && den == 1; }
  bool operator!=(const num& n) const { return !(*this == n); }

  // Primitive operand

  frac& operator=(ll n){ *this = frac(n, 1); }
  bool operator==(ll n) const { return *this == num(n); }
  bool operator!=(ll n) const { return !(*this == n); }

};


#endif
