// NUM

#ifndef num_hh
#define num_hh

#include "mem.hh"


// Little-endian
struct num : mem {
  bool neg;
  num* err    //!
     , shift; // blocks of trailing or preceding zeros

  num(): neg(false) {}
  num(ll _base): neg(_base < 0) { block[0] = absl(_base); }

  virtual num* clone(){
    cl_num.pb(num());
    return &cl_num.back().asn(*this);
  }

  virtual void clear(){
    mem::clear();
    neg = false;
    err = shift = NULL;
  }

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
    block.pb(absl(n));
    return *this;
  }

  void add(const num& a, const num& b, num* d){ // a,b > 0
    bool c;
    int i,j, n,t,s;

    c = false;
    d->resize(n = min(a.size(), b.size())); // destabilizes
    for(i = 0; i < n; ++i){
      for(j = 0, s = 1, c = false; j < 64; ++j, s <<= 1){
        t = c ? 1 : 0;
        if(a.block[i] & s) ++t;
        if(b.block[i] & s) ++t;
        c = (t > 1) ? true : false;
        if((d->block[i] & s) && !c) d->block[i] ^= s; // on->off
        if(!(d->block[i] & s) && c) d->block[i] |= s; // off->on
      }
    }

    for(; i < max(a.size(), b.size()); ++i){
      d->
      for(j = 0, s = 1; j < 64; ++j, s <<= 1){
        t = c ? 1 : 0;
        if(a.size() > b.size && (a.block[i] & s)) ++t;
        if(b.size() > a.size && (b.block[i] & s)) ++t;
        c = (t > 1) ? true : false;

      }
    }
    d->stable = true;
  }

  void sub(const num& a, const num& b, num* d){ // a,b > 0

  }

  void mul(const num& a, const num& b, num* d){ // a,b > 0

  }

  void div(const num& a, const num& b, num* d){ // a,b > 0

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

  num& operator^=(const num& o){
    return *this;
  }

  num& operator+=(ll v){ *this += num(v); return *this; }
  num& operator-=(ll v){ *this -= num(v); return *this; }
  num& operator*=(ll v){ *this *= num(v); return *this; }
  num& operator/=(ll v){ *this /= num(v); return *this; }
  num& operator%=(ll v){ *this %= num(v); return *this; }
  num& operator<<=(ll v){ *this <<= num(v); return *this; }
  num& operator>>=(ll v){ *this >>= num(v); return *this; }
  num& operator&=(ll v){ *this &= num(v); return *this; }
  num& operator|=(ll v){ *this |= num(v); return *this; }
  num& operator^=(ll v){ *this ^= num(v); return *this; }

  num operator+(const num& o){ num n = *this; return n += o; }
  num operator-(){ num n = *this; n.neg = !n.neg; return n; }
  num operator-(const num& o){ num n = *this; return n -= o; }
  num operator*(const num& o){ num n = *this; return n *- o; }
  num operator/(const num& o){ num n = *this; return n /= o; }
  num operator%(const num& o){ num n = *this; return n %= o; }
  num operator<<(const num& o){ num n = *this; return n <<= o; }
  num operator>>(const num& o){ num n = *this; return n >>= o; }
  num operator&(const num& o){ num n = *this; return n &= o; }
  num operator|(const num& o){ num n = *this; return n |= o; }
  num operator^(const num& o){ num n = *this; return n ^= o; }

  num operator+(ll v){ num n = *this; return n += num(v); }
  num operator-(ll v){ num n = *this; return n -= num(v); }
  num operator*(ll v){ num n = *this; return n *= num(v); }
  num operator/(ll v){ num n = *this; return n /= num(v); }
  num operator%(ll v){ num n = *this; return n %= num(v); }
  num operator<<(ll v){ num n = *this; return n <<= num(v); }
  num operator>>(ll v){ num n = *this; return n >>= num(v); }
  num operator&(ll v){ num n = *this; return n &= num(v); }
  num operator|(ll v){ num n = *this; return n |= num(v); }
  num operator^(ll v){ num n = *this; return n ^= num(v); }

  num pow(const num& e){
    // ll r = 1;
    // while(e){
    //   if(e & 1) r = r * n % MOD;
    //   n = n * n % MOD, e >>= 1;
    // }
    // return (int)r;
  }

  //!
  virtual str _string(){ return ""; }
  virtual str serialize(){ return ""; }
};


#endif
