// CUBE

#ifndef cube_hh
#define cube_hh

#include "glb.hh"


const int MAX_ITEMS_PER_SUBCUBE = 1;

enum Dir0 {
  T, N, E, S, W, B
};
enum Dir1 {
  TNW, TNE, TSE, TSW, BNW, BNE, BSE, BSW
};

struct item {
  vector<double> data;
  item(){}
};

struct cube {
  item val;
  vec<double> lbd, ubd; // Lower/upper xyz bounds
  cube* adj[6]; // Adjacent subcubes
  cube* ntr[8]; // Interior subcubes

  cube(){}
  cube(vec<item>& v){
    fill(v);
  }

  void fill(vec<item>& v){
    int i;
    for(i = 0; i < v[0].data.size(); ++i)
      lbd.pb(DBL_MIN), ubd.pb(DBL_MAX);
    for(item& t : v){
      insert(t);
      for(i = 0; i < t.data.size(); ++i){
        lbd[i] = min(t.data[i], lbd[i]);
        ubd[i] = max(t.data[i], ubd[i]);
      }
    }
  }

  void insert(item& inp){
    int i;
    if(val.data.empty()){
      val = inp;
      return;
    }

    if(ntr[TNW] == NULL){
      for(i = 0; i < 8; ++i)
        cl_cube.pb(cube()), ntr[i] = &cl_cube.back();
      ntr[TNW]->adj[E] = ntr[TSE]->adj[N] = ntr[BNE]->adj[T] = ntr[TNE];
      ntr[TNW]->adj[S] = ntr[TSE]->adj[W] = ntr[BSW]->adj[T] = ntr[TSW];
      ntr[TNW]->adj[B] = ntr[BNE]->adj[W] = ntr[BSW]->adj[N] = ntr[BNW];
      ntr[TNE]->adj[S] = ntr[TSW]->adj[E] = ntr[BSE]->adj[T] = ntr[TSE];
      ntr[TNE]->adj[W] = ntr[TSW]->adj[N] = ntr[BNW]->adj[T] = ntr[TNW];
      ntr[TNE]->adj[B] = ntr[BNW]->adj[E] = ntr[BSE]->adj[N] = ntr[BNE];
      ntr[TSE]->adj[B] = ntr[BNE]->adj[S] = ntr[BSW]->adj[E] = ntr[BSE];
      ntr[TSW]->adj[B] = ntr[BNW]->adj[S] = ntr[BSE]->adj[W] = ntr[BSW];
    }

    //! Place into subcube based on bounds and inp.data
  }
};


#endif
