// STR

#ifndef str_hh
#define str_hh

#include "def.hh"


struct str : std::string {
  str(){}
  str(const char* s): std::string(s) {}
  str(std::string s){ *this = s; }

  str lcsseq(const str& o){

  }

  str lcsstr(const str& o){

  }
};


#endif
