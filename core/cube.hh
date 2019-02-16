// CUBE

#ifndef cube_hh
#define cube_hh

#include "glb.hh"


template<typename T, typename Comp = std::less<T> >
struct item {
  vector<T> data;

  item(){}
};


struct cube {
  item val;
  cube* adj[6]; // T N E S W B
  cube* ntr[8]; // TNW TNE TSE TSW BNW BNE BSE BSW

  cube(){}
  cube(vec<item>& v){
    for(item& i : v)
      insert(i);
  }

  void insert(item& inp){

  }
};


#endif
