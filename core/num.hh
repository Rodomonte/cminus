// NUM

#ifndef num_hh
#define num_hh

#include "mem.hh"


// Little-endian
struct num : mem {
  bool neg;
  num* err    //!
     , shift; //! blocks of trailing or preceding zeros

  num(): neg(false) {}
  num(ll n): neg(n < 0) { (*this)[0] = absl(n); }

  num(double d): neg(d < 0.0) {
    double n = 1.0;
    while(n < d)
      n *= 2.0;
    n *= 0.5;
    while(d > 0.0){
      if(d < 1.0) shift = shift ? shift - 1 : num(-1);
      (*this)[0] <<= 1;
      if(d >= n) (*this)[0] |= 1, d -= n;
    }
  }

  virtual num* clone(){ cl_num.pb(*this); return &cl_num.back(); }
  virtual void clear(){ mem::clear(); neg = false; err = shift = NULL; }

  //!
  virtual str _string(){ return ""; }
  virtual str serialize(){ return ""; }

  void _add(const num& a, const num& b, num* d){ // a,b > 0
    bool c;
    int i,j, n,t,s;
    num x;

    c = false, n = min(a.size(), b.size());
    if(d->size() < n) d->resize(n);
    for(i = 0; i < n; ++i){
      for(j = 0, s = 1, c = false; j < 64; ++j, s <<= 1){
        t = c ? 1 : 0;
        if(a[i] & s) ++t;
        if(b[i] & s) ++t;
        c = (t > 1) ? true : false;
        if(((*d)[i] & s) && !(t & 1)) (*d)[i] ^= s; // on->off
        if(!((*d)[i] & s) && (t & 1)) (*d)[i] |= s; // off->on
      }
    }

    n = max(a.size(), b.size());
    d->resize(n);
    for(; i < n; ++i){
      for(j = 0, s = 1; j < 64; ++j, s <<= 1){
        t = c ? 1 : 0;
        if(a.size() > b.size && (a[i] & s)) ++t;
        if(b.size() > a.size && (b[i] & s)) ++t;
        c = (t > 1) ? true : false;
        if(t & 1) (*d)[i] |= s;
      }
    }

    if(c) d->extend(), d->block.back() = 1;
    x = (a.shift ? *a.shift : num(0)) + (b.shift ? *b.shift : 0);
    if(x()) d->shift = x.clone();
  }

  void _sub(const num& a, const num& b, num* d){ // a,b > 0

  }

  void _mul(const num& a, const num& b, num* d){ // a,b > 0

  }

  void _div(const num& a, const num& b, num* d){ // a,b > 0

  }

  void _pow(const num& n, const num& e, num* d){ // a,b > 0
    // ll r = 1;
    // while(e){
    //   if(e & 1) r = r * n % MOD;
    //   n = n * n % MOD, e >>= 1;
    // }
    // return (int)r;
  }

  void _and(const num& a, const num& b, num* d){ // a,b > 0

  }

  void _or(const num& a, const num& b, num* d){ // a,b > 0

  }

  void _xor(const num& a, const num& b, num* d){ // a,b > 0

  }
  num xor(const num& o){ num n; _xor(*this, o, &n); return n; }

  bool operator()(){ return *this != 0; }
  bool operator==(const num& o){
    if(neg != o.neg || (shift && !o.shift) || (!shift && o.shift) ||
       (shift && o.shift && *shift != *(o.shift))) return false;
    return mem::operator==(o);
  }
  bool operator!=(const num& o){ return !(*this == o); }

  bool operator<(const num& o){
    if(neg && !o.neg) return true;
    if(!neg && o.neg) return false;
    num x = size() + (shift ? *shift : 0)
      , y = o.size() + (o.shift ? *(o.shift) : 0);
    if(x < y) return true;
    if(x > y) return false;

    int i;
    if(neg){
      for(i = 0; i < min(size(), o.size()); ++i){
        if((*this)[i] < o[i]) return false;
        if((*this)[i] > o[i]) return true;
      }
      if((shift ? *shift : 0) < (o.shift ? *(o.shift) : 0)) return true;
      return false;

    }else{
      for(i = min(size(), o.size())-1; i >= 0; --i){
        if((*this)[i] < o[i]) return true;
        if((*this)[i] > o[i]) return false;
      }
      if((shift ? *shift : 0) <= (o.shift ? *(o.shift) : 0)) return false;
      return true;
    }
  }

  bool operator>(const num& o){ return !(*this < o) && !(*this && o); }
  bool operator<=(const num& o){ return !(*this > o); }
  bool operator>=(const num& o){ return !(*this < o); }

  bool operator==(ll n){ return *this == num(n); }
  bool operator!=(ll n){ return *this != num(n); }
  bool operator<(ll n){ return *this < num(n); }
  bool operator>(ll n){ return *this > num(n); }
  bool operator<=(ll n){ return *this <= num(n); }
  bool operator>=(ll n){ return *this >= num(n); }

  num& operator=(const num& o){
    clear();
    neg = o.neg;
    if(o.err)
      cl_num.pb(*(o.err));
    block = o.block;
    return *this;
  }

  num& operator=(ll n){
    clear();
    neg = (n < 0);
    (*this)[0] = absl(n);
    return *this;
  }

  num& operator+=(const num& o){
    if(neg && !o.neg){
      neg = false;
      if(*this == o) *this = 0;
      else if(*this < o) sub(o, *this, this);
      else sub(*this, o, this), neg = true;

    }else if(!neg && o.neg){
      o.neg = false;
      if(*this == o) *this = 0;
      else if(*this < o) sub(o, *this, this), neg = true;
      else sub(*this, o, this);

    }else add(*this, o, this);
    return *this;
  }

  num& operator-=(const num& o){
    return *this;
  }

  num& operator*=(const num& o){
    return *this;
  }

  num& operator/=(const num& o){
    return *this;
  }

  num operator%=(const num& o){
    return *this;
  }

  num& operator^=(const num& o){
    return *this;
  }

  num& operator<<=(const num& o){
    return *this;
  }

  num& operator>>=(const num& o){
    return *this;
  }

  num& operator&=(const num& o){
    return *this;
  }

  num& operator|=(const num& o){
    return *this;
  }

  num& operator+=(ll v){ *this += num(v); return *this; }
  num& operator-=(ll v){ *this -= num(v); return *this; }
  num& operator*=(ll v){ *this *= num(v); return *this; }
  num& operator/=(ll v){ *this /= num(v); return *this; }
  num& operator%=(ll v){ *this %= num(v); return *this; }
  num& operator^=(ll v){ *this ^= num(v); return *this; }

  num& operator++(){ return *this += 1; }
  num operator++(int u){ num r(*this); *this += 1; return r; }
  num& operator--(){ return *this -= 1; }
  num operator--(int u){ return *this - 1; }

  num& operator<<=(ll v){ *this <<= num(v); return *this; }
  num& operator>>=(ll v){ *this >>= num(v); return *this; }
  num& operator&=(ll v){ *this &= num(v); return *this; }
  num& operator|=(ll v){ *this |= num(v); return *this; }

  num operator+(const num& o){ num n = *this; return n += o; }
  num operator-(){ num n = *this; n.neg = !n.neg; return n; }
  num operator-(const num& o){ num n = *this; return n -= o; }
  num operator*(const num& o){ num n = *this; return n *- o; }
  num operator/(const num& o){ num n = *this; return n /= o; }
  num operator%(const num& o){ num n = *this; return n %= o; }
  num operator^(const num& o){ num n = *this; return n ^= o; }

  num operator<<(const num& o){ num n = *this; return n <<= o; }
  num operator>>(const num& o){ num n = *this; return n >>= o; }
  num operator&(const num& o){ num n = *this; return n &= o; }
  num operator|(const num& o){ num n = *this; return n |= o; }

  num operator!(){ return (*this == 0) ? num(1) : num(0); }
  num operator~(){
    int i;
    num n;
    for(i = 0; i < size(); ++i)
      (*this)[i] = ~(*this)[i];
    return n;
  }

  num operator+(ll v){ num n = *this; return n += num(v); }
  num operator-(ll v){ num n = *this; return n -= num(v); }
  num operator*(ll v){ num n = *this; return n *= num(v); }
  num operator/(ll v){ num n = *this; return n /= num(v); }
  num operator%(ll v){ num n = *this; return n %= num(v); }
  num operator^(ll v){ num n = *this; return n ^= num(v); }

  num operator<<(ll v){ num n = *this; return n <<= num(v); }
  num operator>>(ll v){ num n = *this; return n >>= num(v); }
  num operator&(ll v){ num n = *this; return n &= num(v); }
  num operator|(ll v){ num n = *this; return n |= num(v); }
};


#endif
