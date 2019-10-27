// NUM

#ifndef num_hh
#define num_hh

#include "mem.hh"

#define SHIFT_MAX 100000000


// Little-endian
struct num : mem {
  bool neg;
  int len;
  num *err; //!

  num(){ *this = 0; }
  num(ll _num){ *this = _num; }
  num(const num& _num){ *this = _num; }

  num& operator=(ll n){
    clear();
    err = NULL;
    neg = (n < 0);
    (*this)[0] = rev(absl(n));
    setlen();
    return *this;
  }

  num& operator=(const num& o){
    neg = o.neg;
    if(o.err) cl_num.pb(*(o.err)), err = &cl_num.back();
    else err = NULL;
    block = o.block;
    len = o.len;
    return *this;
  }

  virtual num* clone() const { cl_num.pb(*this); return &cl_num.back(); }
  virtual str serialize() const { return ""; } //!

  virtual int _int() const { return (rev(block[0]) & 0xFFFF) * (neg ? -1 : 1); }

  virtual str _string() const {
    if(!(*this)) return str("0");
    int i,j;
    str s;
    if(neg) s += "-";
    for(i = 0; i < size(); ++i){
      for(j = 63; j >= 0; --j){
        if(at(i) & (1LLU << j)) s += "1";
        else s += "0";
      }
    }
    return s;
  }

  virtual void fix(){
    while(size() > 1 && !back())
      block.pop_back();
    setlen();
    if(size() == 1 && at(0) == 0) neg = false;
  }

  void setlen(){
    int i;
    llu s;
    if(size() == 1 && back() == 0){ len = 1; return; }
    for(i = 0, s = 1; i < 64; ++i, s <<= 1)
      if(back() & s) break;
    len = (size() - 1) * 64 + (64 - i);
  }

  void setbit(int i, llu m, bool b){
    while(size() <= i)
      block.pb(0);
    if(!b && (at(i) & m)){
      (*this)[i] ^= m;
      while(size() && !block.back())
        block.pop_back();
    }else if(b && !(at(i) & m)) (*this)[i] |= m;
    fix();
  }

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
        d->setbit(i, s, t & 1);
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
        d->setbit(i, s, t & 1);
      }
    }
    if(c) d->extend(), d->block.back() = 1;
    d->fix();
  }

  void _sub(const num& a, const num& b, num* d) const { // a > b > 0
    bool c;
    int i,j, n,t;
    llu s;
    num x,y;

    for(i = 0; i < b.size(); ++i){
      if(d->size() < i+1) d->resize(i+1);
      for(j = 0, s = (1LLU << 63), c = false; j < 64; ++j, s >>= 1){
        if((a.at(i) & s) && !(b.at(i) & s)) d->setbit(i, s, !c), c = false;
        else if(!(a.at(i) & s) && (b.at(i) & s)) d->setbit(i, s, !c), c = true;
        else d->setbit(i, s, c);
      }
    }

    for(; i < a.size(); ++i){
      if(d->size() < i+1) d->resize(i+1);
      for(j = 0, s = (1LLU << 63); j < 64; ++j, s >>= 1){
        if(c || !(a.at(i) & s)){
          d->setbit(i, s, 0);
          if(a.at(i) & s) c = false;
        }else if(a.at(i) & s) d->setbit(i, s, 1);
      }
    }
    d->fix();
  }

  void split_num(const num& a, num* lo, num* hi, int m) const {
    *lo = (a & ((num(1) << m) - 1));
    *hi = (a >> m);
  }

  num karatsuba(const num& a, const num& b) const {
    if(!a || !b) return num(0);
    if(a == 1) return b;
    if(b == 1) return a;
    int m;
    num c,d,e, w,x,y,z;
    m = (min(a.len, b.len) >> 1);
    split_num(a, &w, &x, m);
    split_num(b, &y, &z, m);
    c = karatsuba(w, y);
    d = karatsuba(w + x, y + z);
    e = karatsuba(x, z);
    return (e << (m << 1)) + ((d - c - e) << m) + c;
  }

  void _mul(const num& a, const num& b, num* d) const { // a,b > 0
    if(a < (1LLU << 31) && b < (1LLU << 31)){
      *d = num((ll)rev(a.at(0)) * (ll)rev(b.at(0)));
      return;
    }
    *d = karatsuba(a, b);
  }

  num divide(const num& a, const num& b, int ret) const {
    int i,j;
    num q,r;
    for(i = a.size()-1; i >= 0; --i){
      j = 0;
      if(i == a.size()-1)
        while(!(a.at(i) & (1LLU << j)))
          ++j;
      for(; j < 64; ++j){
        r <<= 1;
        r.setbit(0, 1LLU << 63, a.at(i) & (1LLU << j));
        if(r >= b) r -= b, q.setbit(i, 1LLU << j, 1);
      }
    }
    if(ret == 1) return q;
    else if(ret == 2) return r;
    else kill("Wrong 3rd parameter to divide()");
  }

  void _div(const num& a, const num& b, num* d) const { // a,b > 0
    if(a < (1LLU << 31) && b < (1LLU << 31)){
      *d = num((ll)rev(a.at(0)) / (ll)rev(b.at(0)));
      return;
    }
    *d = divide(a, b, 1);
  }

  void _mod(const num& a, const num& b, num* d) const { // a,b > 0
    if(a < (1LLU << 31) && b < (1LLU << 31)){
      *d = num((ll)rev(a.at(0)) % (ll)rev(b.at(0)));
      return;
    }
    *d = divide(a, b, 2);
  }

  void _pow(const num& n, const num& e, num* d) const { // a,b > 0
    num r(1), s(n), t(e);
    while(t()){
      if((t & 1)()) r *= s;
      s *= s, t >>= 1;
    }
    *d = r;
  }

  // Actually shifts right due to little-endianness
  void _lshift(const num& a, int b, num* d) const { // a,b > 0
    int i,j,k,l;
    i = a.size() - 1, j = a.len % 64, j = j ? 64 - j : 0;
    d->len = a.len + b;
    d->resize((d->len + 63) >> 6);
    k = d->size() - 1, l = d->len % 64, l = l ? 64 - l : 0;
    while(i >= 0){
      if((a.at(i) & (1LLU << j)) && !((*d)[k] & (1LLU << l)))
        (*d)[k] |= (1LLU << l);
      else if(!(a.at(i) & (1LLU << j)) && ((*d)[k] & (1LLU << l)))
        (*d)[k] ^= (1LLU << l);
      if(j == 63) j = 0, --i;
      else ++j;
      if(l == 63) l = 0, --k;
      else ++l;
    }
    while(k >= 0){
      if((*d)[k] & (1LLU << l)) (*d)[k] ^= (1LLU << l);
      if(l == 63) l = 0, --k;
      else ++l;
    }
  }

  // Actually shifts left due to little-endianness
  void _rshift(const num& a, int b, num* d) const { // a,b > 0
    if(b >= a.len){ *d = 0, d->len = 1; return; }
    int i,j,k,l;
    i = (b >> 6), j = b % 64;
    k = l = 0;
    while((i << 6) + j <= a.len){
      if((a.at(i) & (1LLU << (63 - j))) && !((*d)[k] & (1LLU << (63 - l))))
        (*d)[k] |= (1LLU << (63 - l));
      else if(!(a.at(i) & (1LLU << (63 - j))) && ((*d)[k] & (1LLU << (63 - l))))
        (*d)[k] ^= (1LLU << (63 - l));
      if(j == 63) j = 0, ++i;
      else ++j;
      if(l == 63) l = 0, ++k;
      else ++l;
    }
    while((k << 6) + l <= a.len){
      if(a.at(k) & (1LLU << (63 - l))) (*d)[k] ^= (1LLU << (63 - l));
      if(l == 63) l = 0, ++k;
      else ++l;
    }
    d->len = a.len - b;
    d->resize((d->len + 63) >> 6);
  }

  void _bitand(const num& a, const num& b, num* d) const { // a,b > 0
    int i,j,n;
    n = min(a.size(), b.size());
    d->resize(n);
    for(i = 0; i < n; ++i){
      for(j = 0; j < 64; ++j){
        if(!((a.at(i) & (1LLU << j)) && (b.at(i) & (1LLU << j))) &&
           ((*d)[i] & (1LLU << j))) (*d)[i] ^= (1LLU << j);
        else if(((a.at(i) & (1LLU << j)) && (b.at(i) & (1LLU << j))) &&
           !((*d)[i] & (1LLU << j))) (*d)[i] |= (1LLU << j);
      }
    }
    d->fix();
  }

  void _bitor(const num& a, const num& b, num* d) const { // a,b > 0
    int i,j,n;
    n = max(a.size(), b.size());
    d->resize(n);
    for(i = 0; i < n; ++i){
      for(j = 0; j < 64; ++j){
        if((!(a.at(i) & (1LLU << j)) && !(b.at(i) & (1LLU << j))) &&
           ((*d)[i] & (1LLU << j))) (*d)[i] ^= (1LLU << j);
        else if(((a.at(i) & (1LLU << j)) || (b.at(i) & (1LLU << j))) &&
           !((*d)[i] & (1LLU << j))) (*d)[i] |= (1LLU << j);
      }
    }
    d->fix();
  }

  void _xor(const num& a, const num& b, num* d) const { // a,b > 0
    int i,j,n;
    n = max(a.size(), b.size());
    for(i = 0; i < n; ++i){
      for(j = 0; j < 64; ++j){
        if(((!(a.at(i) & (1LLU << j)) && !(b.at(i) & (1LLU << j))) ||
           ((a.at(i) & (1LLU << j)) && (b.at(i) & (1LLU << j)))) &&
           ((*d)[i] & (1LLU << j))) (*d)[i] ^= (1LLU << j);
        else if((((a.at(i) & (1LLU << j)) && !(b.at(i) & (1LLU << j))) ||
           (!(a.at(i) & (1LLU << j)) && (b.at(i) & (1LLU << j)))) &&
           !((*d)[i] & (1LLU << j))) (*d)[i] |= (1LLU << j);
      }
    }
    d->fix();
  }

  virtual num abs() const { num r(*this); r.neg = false; return r; }
  num gcd(const num& o) const { return (o() ? o.gcd(*this % o) : *this).abs(); }
  num lcm(const num& o) const { return (*this / gcd(o) * o).abs(); }

  bool operator()() const { return *this != 0; }
  bool operator!() const { return *this == 0; }

  num operator-() const {
    num n(*this);
    if((*this)()) n.neg = !n.neg;
    return n;
  }

  num operator~() const {
    int i;
    num n(*this);
    for(i = 0; i < size(); ++i)
      n[i] = ~n[i];
    n.fix();
    return n;
  }

  bool operator==(const num& o) const {
    if(neg != o.neg || len != o.len) return false;
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

  num& operator++(){ return *this += 1; } // pre
  num operator++(int u){ num r(*this); *this += 1; return r; } // post
  num& operator--(){ return *this -= 1; } // pre
  num operator--(int u){ num r(*this); *this -= 1; return r; } // post

  num& operator+=(const num& o){
    if(!(*this)) *this = o;
    else if(!o) return *this;
    else if(neg && !o.neg){
      neg = false;
      if(*this == o) *this = 0;
      else if(*this < o) _sub(o, *this, this);
      else _sub(*this, o, this), neg = true;
    }else if(!neg && o.neg){
      neg = true;
      if(*this == o) *this = 0, neg = false;
      else if(*this > o) _sub(o, *this, this);
      else _sub(*this, o, this), neg = false;
    }else _add(*this, o, this);
    return *this;
  }

  num& operator-=(const num& o){
    if(!(*this)) *this = -o;
    else if(!o) return *this;
    else if(neg && o.neg){
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
    bool _neg = (*this)() && o() && ((neg && !o.neg) || (!neg && o.neg));
    num _o(o);
    neg = _o.neg = false;
    _mul(*this, _o, this);
    neg = _neg;
    return *this;
  }

  num& operator/=(const num& o){
    if(!o) kill("Divide by zero");
    bool _neg = (*this)() && ((neg && !o.neg) || (!neg && o.neg));
    num _o(o);
    neg = _o.neg = false;
    _div(*this, _o, this);
    neg = *this != 0 && _neg;
    return *this;
  }

  num& operator%=(const num& o){
    if(!o) kill("Modulo zero");
    bool _neg = (*this)() && ((neg && !o.neg) || (!neg && o.neg));
    num _o(o);
    neg = _o.neg = false;
    _mod(*this, _o, this);
    neg = *this != 0 && _neg;
    return *this;
  }

  num& operator^=(const num& o){
    if(o < 0) kill("Negative power");
    bool _neg = neg;
    neg = false;
    _pow(*this, o, this);
    neg = _neg && (o & 1)();
    return *this;
  }

  num& operator<<=(const num& o){
    if(o + (size()<<6) >= SHIFT_MAX) kill("Shift max exceeded\n");
    int n = o._int();
    if(n < 0) _rshift(*this, -n, this);
    _lshift(*this, n, this);
    return *this;
  }

  num& operator>>=(const num& o){
    int n = o._int();
    if(n < 0) _lshift(*this, -n, this);
    _rshift(*this, n, this);
    return *this;
  }

  num& operator&=(const num& o){
    _bitand(*this, o, this);
    return *this;
  }

  num& operator|=(const num& o){
    _bitor(*this, o, this);
    return *this;
  }

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
  num XOR(const num& o) const { num n; _xor(*this, o, &n); return n; }

  bool operator&&(const num& o) const { return *this != 0 && o != 0; }
  bool operator||(const num& o) const { return *this != 0 || o != 0; }
};


#endif
