// STR

#ifndef str_hh
#define str_hh

#include "def.hh"


struct str : std::string {
  str(){}
  str(const char* s): std::string(s) {}
  str(std::string s){ *this = s; }

  str* clone(){ cl_str.pb(*this); return &cl_str.back(); }

  str lcsseq(const str& o){

  }

  str lcsstr(const str& o){

  }
};


#endif
