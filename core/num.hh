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

  num& asn(const num& o){
    neg = o.neg;
    if(o.err)
      cl_num.pb(*(o.err));
    block = o.block;
    return *this;
  }

  num& operator=(const num& o){
    asn(o);
    return *this;
  }

  num& operator+=(const num& o){
    // if(
    // int i;
    // for(i = 0; i < block.size(); ++i)

    return *this;
  }

  num operator-=(const num& o){

  }

  num operator*=(const num& o){

  }

  num operator/=(const num& o){

  }

  num operator%=(const num& o){

  }

  num operator+(const num& o){ num n = *this; return n += o; }
  num operator-(){ num n = *this; n.neg = !n.neg; return n; }
  num operator-(const num& o){ num n = *this; return n -= o; }
  num operator*(const num& o){ num n = *this; return n *- o; }
  num operator/(const num& o){ num n = *this; return n /= o; }
  num operator%(const num& o){ num n = *this; return n %= o; }

  bool operator==(const num& o){
    if(neg != o.neg || (shift && !o.shift) || (!shift && o.shift) ||
       (shift && o.shift && *shift != *(o.shift))) return false;
    return mem::operator==(o);
  }
  bool operator!=(const num& o){ return !(*this == o); }

  bool operator<(const num& o){
    // if(neg && !o.neg) return true;
    // if(!neg &&
  }

  bool operator>(const num& o){ }
  bool operator<=(const num& o){ }
  bool operator>=(const num& o){ }

  num pow(const num& e){

  }

  str _string(){
    return ""; //!
  }

  str serialize(){
    return ""; //!
  }
};


#endif
