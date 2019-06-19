// NUM

#ifndef num_hh
#define num_hh

#include "mem.hh"


// Little-endian
struct num : mem {
  bool neg;
  int len;
  num *err; //!

  num(): neg(false), len(1), err(NULL) {}
  num(ll n): neg(n < 0), err(NULL) {
    int i;
    (*this)[0] = rev(absl(n));
    for(i = 63; i >= 0; --i)
      if((1LLU << i) & at(0)) break;
    len = i+1;
  }
  num(int n): num((ll)n) {}
  num(const num& o){ *this = o; }

  virtual num* clone() const { cl_num.pb(*this); return &cl_num.back(); }
  virtual void clear(){ mem::clear(), neg = false, len = 1, err = NULL; }

  int _int() const { return (rev(block[0]) & 0xFFFF) * (neg ? -1 : 1); }

  virtual str _string() const {
    if(!(*this)) return str('0');
    int i;
    str s;
    num n(*this);
    vec<char> v;

    // while(n > 0)
    //   v.pb(rev((n % 10)[0]) & 0xFF), n /= 10;
    // if(neg) s = str("-");
    // for(i = v.size()-1; i >= 0; --i)
    //   s += str(v[i] + '0');
    return s;
  }

  //!
  virtual str serialize() const { return ""; }

  void _add(const num& a, const num& b, num* d) const { // a,b > 0
    bool c;
    int i,j, n,t;
    llu s;
    num x,y;

    n = min(a.size(), b.size());
    for(i = 0; i < n; ++i){
      if(d->size() < i+1) d->resize(i+1);
      for(j = 0, s = (1LLU << 63), c = false; j < 64; ++j, s >>= 1){
        t = c ? 1 : 0;
        if(a.at(i) & s) ++t;
        if(b.at(i) & s) ++t;
        c = (t > 1) ? true : false;
        if(!(t & 1) && ((*d)[i] & s)) (*d)[i] ^= s; // on->off
        else if((t & 1) && !((*d)[i] & s)) (*d)[i] |= s; // off->on
      }
    }

    n = max(a.size(), b.size());
    for(; i < n; ++i){
      if(d->size() < i+1) d->resize(i+1);
      for(j = 0, s = (1LLU << 63); j < 64; ++j, s >>= 1){
        t = c ? 1 : 0;
        if(a.size() > b.size() && (a.at(i) & s)) ++t;
        if(b.size() > a.size() && (b.at(i) & s)) ++t;
        c = (t > 1) ? true : false;
        if(!(t & 1) && ((*d)[i] & s)) (*d)[i] ^= s;
        else if((t & 1) && !((*d)[i] & s)) (*d)[i] |= s;
      }
    }
    if(c) d->extend(), d->block.back() = 1;
  }

  void _sub(const num& a, const num& b, num* d) const { // a > b > 0
    bool c;
    int i,j, n,t;
    llu s;
    num x,y;

    for(i = 0; i < b.size(); ++i){
      if(d->size() < i+1) d->resize(i+1);
      for(j = 0, s = (1LLU << 63), c = false; j < 64; ++j, s >>= 1){
        if((a.at(i) & s) && (b.at(i) & s)){
          if(c && !((*d)[i] & s)) (*d)[i] |= s;
          else if(!c && ((*d)[i] & s)) (*d)[i] ^= s;
        }else if((a.at(i) & s) && !(b.at(i) & s)){
          if(c){
            c = false;
            if((*d)[i] & s) (*d)[i] ^= s;
          }else if(!c && !((*d)[i] & s)) (*d)[i] |= s;
        }else if(!(a.at(i) & s) && (b.at(i) & s)){
          if(!c){
            c = true;
            if(!((*d)[i] & s)) (*d)[i] |= s;
          }else if(c && ((*d)[i] & s)) (*d)[i] ^= s;
        }
      }
    }

    for(; i < a.size(); ++i){
      if(d->size() < i+1) d->resize(i+1);
    }
  }

  void _mul(const num& a, const num& b, num* d) const { // a,b > 0

  }

  void _div(const num& a, const num& b, num* d) const { // a,b > 0

  }

  void _mod(const num& a, const num& b, num* d) const { // a,b > 0

  }

  void _pow(const num& n, const num& e, num* d) const { // a,b > 0
    // ll r = 1;
    // while(e){
    //   if(e & 1) r = r * n % MOD;
    //   n = n * n % MOD, e >>= 1;
    // }
    // return (int)r;
  }

  void _lshift(const num& a, int b, num* d) const { // a,b > 0
    int i,j;
    llu s;
    num n;
    // for(j = 0, s = (1LLU << 63); j < 64; ++j, s >>= 1)
  }

  void _rshift(const num& a, int b, num* d) const { // a,b > 0

  }

  void _and(const num& a, const num& b, num* d) const { // a,b > 0

  }

  void _or(const num& a, const num& b, num* d) const { // a,b > 0

  }

  void _xor(const num& a, const num& b, num* d) const { // a,b > 0

  }

  bool operator()() const { return *this != 0; }
  bool operator==(const num& o) const {
    if(neg != o.neg) return false;
    return mem::operator==(o);
  }
  bool operator!=(const num& o) const { return !(*this == o); }

  bool llu_lt(llu a, llu b) const {
    int i;
    for(i = 0; i < 64; ++i){
      if((a & (1LLU << i)) < (b & (1LLU << i))) return true;
      if((a & (1LLU << i)) > (b & (1LLU << i))) return false;
    }
    return false;
  }

  bool operator<(const num& o) const {
    if(neg && !o.neg) return true;
    if(!neg && o.neg) return false;
    if(size() < o.size()) return true;
    if(size() > o.size()) return false;

    int i;
    if(neg){
      for(i = 0; i < size(); ++i){
        if(llu_lt(at(i), o.at(i))) return false;
        if(llu_lt(o.at(i), at(i))) return true;
      }
      return false;

    }else{
      for(i = size()-1; i >= 0; --i){
        if(llu_lt(at(i), o.at(i))) return true;
        if(llu_lt(o.at(i), at(i))) return false;
      }
      return false;
    }
  }

  bool operator>(const num& o) const { return !(*this < o) && !(*this == o); }
  bool operator<=(const num& o) const { return !(*this > o); }
  bool operator>=(const num& o) const { return !(*this < o); }

  bool operator==(ll n) const { return *this == num(n); }
  bool operator!=(ll n) const { return *this != num(n); }
  bool operator<(ll n) const { return *this < num(n); }
  bool operator>(ll n) const { return *this > num(n); }
  bool operator<=(ll n) const { return *this <= num(n); }
  bool operator>=(ll n) const { return *this >= num(n); }

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
    (*this)[0] = rev(absl(n));
    return *this;
  }

  num& operator+=(const num& o){
    if(neg && !o.neg){
      neg = false;
      if(*this == o) *this = 0;
      else if(*this < o) _sub(o, *this, this);
      else _sub(*this, o, this), neg = true;
    }else if(!neg && o.neg){
      neg = true;
      if(*this == o) *this = 0, neg = false;
      else if(*this < o) _sub(o, *this, this);
      else _sub(*this, o, this), neg = false;
    }else _add(*this, o, this);
    return *this;
  }

  num& operator-=(const num& o){
    if(neg && o.neg){
      if(*this == o) *this = 0;
      else if(*this < o) _sub(o, *this, this);
      else _sub(*this, o, this), neg = true;
    }else if(!neg && !o.neg){
      if(*this == o) *this = 0;
      else if(*this < o) _sub(o, *this, this), neg = true;
      else _sub(*this, o, this);
    }else _add(*this, o, this);
    return *this;
  }

  num& operator*=(const num& o){
    _mul(*this, o, this);
    neg = ((neg && !o.neg) || (!neg && o.neg));
    return *this;
  }

  num& operator/=(const num& o){
    if(!o) kill("Divide by zero");
    _div(*this, o, this);
    neg = ((neg && !o.neg) || (!neg && o.neg));
    return *this;
  }

  num& operator%=(const num& o){
    if(!o) kill("Modulo zero");
    _mod(*this, o, this);
    neg = ((neg && !o.neg) || (!neg && o.neg));
    return *this;
  }

  num& operator^=(const num& o){
    _pow(*this, o, this);
    //! o < 0: 1 / ans
    if(*this < 0 && !(o & 1)()) neg = false;
    return *this;
  }

  num& operator<<=(const num& o){
    int n = o._int();
    if(n < 0) _rshift(*this, -n, this);
    _lshift(*this, n, this);
    return *this;
  }

  num& operator>>=(const num& o){
    if(o + (size()<<6) >= SHIFT_MAX) kill("Shift max exceeded\n");
    int n = o._int();
    if(n < 0) _lshift(*this, -n, this);
    _rshift(*this, n, this);
    return *this;
  }

  num& operator&=(const num& o){
    _and(*this, o, this);
    return *this;
  }

  num& operator|=(const num& o){
    _or(*this, o, this);
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

  num operator+(const num& o) const { num n(*this); n += o; return n; }
  num operator-(const num& o) const { num n(*this); n -= o; return n; }
  num operator*(const num& o) const { num n(*this); n *= o; return n; }
  num operator/(const num& o) const { num n(*this); n /= o; return n; }
  num operator%(const num& o) const { num n(*this); n %= o; return n; }
  num operator^(const num& o) const { num n(*this); n ^= o; return n; }

  num operator<<(const num& o) const { num n(*this); n <<= o; return n; }
  num operator>>(const num& o) const { num n(*this); n >>= o; return n; }
  num operator&(const num& o) const { num n(*this); n &= o; return n; }
  num operator|(const num& o) const { num n(*this); n |= o; return n; }
  num operator||(const num& o) const { num n; _xor(*this, o, &n); return n; }

  num operator-() const {
    num n(*this);
    if((*this)()) n.neg = !n.neg;
    return n;
  }
  bool operator!() const { return (*this == 0) ? true : false; }
  num operator~() const {
    int i;
    num n(*this);
    for(i = 0; i < size(); ++i)
      n[i] = ~n[i];
    return n;
  }

  num operator+(ll v) const { num n(*this); n += num(v); return n; }
  num operator-(ll v) const { num n(*this); n -= num(v); return n; }
  num operator*(ll v) const { num n(*this); n *= num(v); return n; }
  num operator/(ll v) const { num n(*this); n /= num(v); return n; }
  num operator%(ll v) const { num n(*this); n %= num(v); return n; }
  num operator^(ll v) const { num n(*this); n ^= num(v); return n; }

  num operator<<(ll v) const { num n(*this); n <<= num(v); return n; }
  num operator>>(ll v) const { num n(*this); n >>= num(v); return n; }
  num operator&(ll v) const { num n(*this); n &= num(v); return n; }
  num operator|(ll v) const { num n(*this); n |= num(v); return n; }
};


#endif
