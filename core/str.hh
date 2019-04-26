// STR

#ifndef str_hh
#define str_hh

#include <string>

#include "glb.hh"


struct str /*: std::string*/ {
  vec<char> v;

  str(){}
  str(char c){ v.pb(c); }
  str(const char* s){ int i; for(i = 0; i < strlen(s); ++i) v.pb(s[i]); }
  str(std::string s){ int i; for(i = 0; i < s.size(); ++i) v.pb(s[i]); }

  int size() const { return v.size(); }
  const char* c_str() const {
    int i;
    for(i = 0; i < size(); ++i)
      buf[i] = v[i];
    buf[i] = 0;
    return std::string(buf).c_str();
  }

  str lcsseq(const str& o) const {

  }

  str lcsstr(const str& o) const {

  }

  char at(int i) const { return v[i]; }
  char& operator[](int i){ return v[i]; }

  bool operator==(const str& o) const {
    if(size() != o.size()) return false;
    int i;
    for(i = 0; i < size(); ++i)
      if(this->at(i) != o.at(i)) return false;
    return true;
  }

  bool operator==(const char* o) const {
    if(size() != strlen(o)) return false;
    int i;
    for(i = 0; i < size(); ++i)
      if(this->at(i) != o[i]) return false;
    return true;
  }

  str& operator=(const str& o){ v = o.v; }
  str& operator+=(const str& o){ v += o.v; }
  str operator+(const str& o) const { str s = *this; s.v += o.v; return s; }
};


#endif
