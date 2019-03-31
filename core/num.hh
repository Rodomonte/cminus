// NUM

#ifndef num_hh
#define num_hh


// Little-endian
struct num : mem {
  bool neg;
  num* err, shift;

  num(): neg(false) { block.pb(0); }
  num(ll _base): neg(_base < 0) { block.pb(_base); }

  num* clone(){
    cl_num.pb(num());
    return &cl_num.back().asn(*this);
  }

  void clear(){
    block.clear();
    block.pb(0);
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

  }

  bool operator>(const num& o){ }
  bool operator<=(const num& o){ }
  bool operator>=(const num& o){ }

  num& operator=(ll n){
    clear();
    neg = (n < 0);
    block.pb(absl(n));
    return *this;
  }

  num& operator=(const num& o){
    clear();
    neg = o.neg;
    if(o.err)
      cl_num.pb(*(o.err));
    block = o.block;
    return *this;
  }

  num& operator+=(const num& o){
    if(neg && !o.neg){
      if(-(*this) == o) *this = 0;
    }
    if(!neg && o.neg){

    }
    int i;
    for(i = 0; i < block.size(); ++i)

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

  str _string(){
    return ""; //!
  }

  str serialize(){
    return ""; //!
  }
};


#endif
