// FRAC

#ifndef frac_hh
#define frac_hh

#include "num.hh"


struct frac : num {
  num den;

  frac(){ *this = 0; }
  frac(ll _num){ *this = _num; }
  frac(const num& _num){ *this = _num; }
  frac(const num& _num, const num& _den): den(_den) {
    num::operator=(_num), reduce();
  }
  frac(const frac& _frac){ *this = _frac; }

  frac& operator=(ll n){ num::operator=(n), den = 1; }
  frac& operator=(const num& n){ num::operator=(n), den = 1; }
  frac& operator=(const frac& o){ num::operator=(o), den = o.den; }

  virtual frac* clone() const { cl_frac.pb(*this); return &cl_frac.back(); }
  virtual str serialize() const { return ""; } //!

  virtual double _double() const { return (double)_int() / den._int(); }
  virtual str _string() const { return num::_string() + "/" + den._string(); }

  virtual void fix(){
    num::fix();
    den.fix();
    reduce();
  }

  void reduce(){
    num g = gcd(den);
    num::operator/=(g);
    den /= g;
  }

  bool operator()() const { return *this != 0; }
  bool operator!() const { return *this == 0; }
  frac operator-() const { return frac(num::operator-(), den); }
  frac operator~() const { return frac(num::operator~(), ~den); }

  bool operator==(const frac& o) const {
    return num::operator==(o) && den == o.den;
  }
  bool operator!=(const frac& o) const { return !(*this == o); }

  bool operator<(const frac& o) const {
    num m = den.lcm(o.den);
    return num::operator*(m / den) < o.num::operator*(m / o.den);
  }
  bool operator>(const frac& o) const { return !(*this < o) && !(*this == o); }
  bool operator<=(const frac& o) const { return !(*this > o); }
  bool operator>=(const frac& o) const { return !(*this < o); }

  frac& operator++(){ return *this += 1; } // pre
  frac operator++(int u){ frac r(*this); *this += 1; return r; } // post
  frac& operator--(){ return *this -= 1; } // pre
  frac operator--(int u){ frac r(*this); *this -= 1; return r; } // post

  frac& operator+=(const frac& o){
    num m = den.lcm(o.den);
    num::operator=(num::operator*(m / den) + o.num::operator*(m / o.den));
    den = m;
    fix();
    return *this;
  }

  frac& operator-=(const frac& o){
    num m = den.lcm(o.den);
    num::operator=(num::operator*(m / den) - o.num::operator*(m / o.den));
    den = m;
    fix();
    return *this;
  }

  frac& operator*=(const frac& o){
    num::operator*=((num)o);
    den *= o.den;
    fix();
    return *this;
  }

  frac& operator/=(const frac& o){
    num::operator*=(o.den);
    den *= (num)o;
    fix();
    return *this;
  }

  frac& operator%=(const frac& o){
    //!
  }
};


#endif
