#ifndef vec_hh
#define vec_hh

#include <vector>

#include "def.hh"


template<typename T>
struct vec : public std::vector<T> {
  vec<T>& operator+=(const vec<T>& o){
    int i;
    for(i = 0; i < o.size(); ++i)
      this->push_back(o[i]);
    return *this;
  }
};


#endif
