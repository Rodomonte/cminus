#ifndef vec_hh
#define vec_hh

#include "incl.hh"


template<class T>
struct vec : std::vector<T> {
  vec<T>& operator+=(const T& t){ this->push_back(t); return *this; }
  vec<T>& operator+=(const vec<T>& o){
    int i;
    for(i = 0; i < o.size(); ++i)
      this->push_back(o[i]);
    return *this;
  }
};


#endif
