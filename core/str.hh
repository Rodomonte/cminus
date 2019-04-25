// STR

#ifndef str_hh
#define str_hh

#include "glb.hh"


struct str : std::string {
  str(){}
  str(const char* s): std::string(s) {}
  str(std::string s){ *this = s; }

  str lcsseq(const str& o){

  }

  str lcsstr(const str& o){

  }

  bool operator==(const str& o){ // O(N)
    if(size() != o.size()) return false;
    int i;
    for(i = 0; i < size(); ++i)
      if((*this)[i] != o[i]) return false;
    return true;
  }

  bool operator==(const char* o){ // O(N)
    if(size() != strlen(o)) return false;
    int i;
    for(i = 0; i < size(); ++i)
      if((*this)[i] != o[i]) return false;
    return true;
  }
};


#endif
