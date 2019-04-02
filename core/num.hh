// NUM

#ifndef num_hh
#define num_hh


// Little-endian
struct num : mem {
  bool neg;
  num* err    //!
     , shift; // blocks of trailing or preceding zeros

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
    num x = block.size() + (shift ? *shift : 0)
      , y = o.block.size() + (o.shift ? *(o.shift) : 0);
    if(x < y) return true;
    if(x > y) return false;

    int i;
    if(neg){
      for(i = 0; i < min(block.size(), o.block.size()); ++i){
        if(block[i] < o.block[i]) return false;
        if(block[i] > o.block[i]) return true;
      }
      if((shift ? *shift : 0) < (o.shift ? *(o.shift) : 0)) return true;
      return false;

    }else{
      for(i = min(block.size(), o.block.size())-1; i >= 0; --i){
        if(block[i] < o.block[i]) return true;
        if(block[i] > o.block[i]) return false;
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
