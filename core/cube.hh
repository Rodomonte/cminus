// CUBE

#ifndef cube_hh
#define cube_hh

#include "glb.hh"


const int MAX_ITEMS_PER_SUBCUBE = 1;

enum Dim {
  X, Y, Z // X=W/E, Y=N/S, Z=T/B
};
enum Adj {
  T, N, E, S, W, B
};
enum Ntr {
  TNW, TNE, TSE, TSW, BNW, BNE, BSE, BSW
};

struct item {
  double data[3];
  item(double x, double y, double z):
    data[X](x), data[Y](y), data[Z](z) {}
};

struct cube {
  item val;
  double lbd[3], ubd[3]; // Lower/upper xyz bounds
  cube* adj[6]; // Adjacent subcubes
  cube* ntr[8]; // Interior subcubes

  cube(){}
  cube(vec<item>& v){
    fill(v);
  }

  // Populate cube
  void fill(vec<item>& v){
    int i;
    for(i = 0; i < v[0].data.size(); ++i)
      lbd.pb(DBL_MAX), ubd.pb(DBL_MIN);
    for(item& t : v)
      for(i = 0; i < t.data.size(); ++i)
        lbd[i] = min(t.data[i], lbd[i]),
        ubd[i] = max(t.data[i], ubd[i]);
    for(item& t : v)
      insert(t);
  }

  // Create 8 subcubes within cube
  void subdivide(){
    int i;
    double hx,hy,hz;
    for(i = 0; i < 8; ++i)
      cl_cube.pb(cube()),
      ntr[i] = &cl_cube.back();

    // Link interior cubes
    ntr[TNW]->adj[E] = ntr[TSE]->adj[N] = ntr[BNE]->adj[T] = ntr[TNE];
    ntr[TNW]->adj[S] = ntr[TSE]->adj[W] = ntr[BSW]->adj[T] = ntr[TSW];
    ntr[TNW]->adj[B] = ntr[BNE]->adj[W] = ntr[BSW]->adj[N] = ntr[BNW];
    ntr[TNE]->adj[S] = ntr[TSW]->adj[E] = ntr[BSE]->adj[T] = ntr[TSE];
    ntr[TNE]->adj[W] = ntr[TSW]->adj[N] = ntr[BNW]->adj[T] = ntr[TNW];
    ntr[TNE]->adj[B] = ntr[BNW]->adj[E] = ntr[BSE]->adj[N] = ntr[BNE];
    ntr[TSE]->adj[B] = ntr[BNE]->adj[S] = ntr[BSW]->adj[E] = ntr[BSE];
    ntr[TSW]->adj[B] = ntr[BNW]->adj[S] = ntr[BSE]->adj[W] = ntr[BSW];

    // Set interior cube bounds
    hx = ubd[X] / 2.0, hy = ubd[Y] / 2.0, hz = ubd[Z] / 2.0;
    ntr[TNW]->lbd[X] = ntr[TSW]->lbd[X] = lbd[X];
    ntr[BNW]->lbd[X] = ntr[BSW]->lbd[X] = lbd[X];

    ntr[TNW]->lbd[Y] = ntr[TNE]->lbd[Y] = lbd[Y];
    ntr[BNW]->lbd[Y] = ntr[BNE]->lbd[Y] = lbd[Y];

    //!
  }

  // Insert one item into cube
  void insert(item& inp){
    int i;
    // If no items in cube, place into outer cube
    if(val.data.empty()){
      val = inp;
      return;
    }

    // Subdivide cube
    if(ntr[TNW] == NULL){
      subdivide();
      //! Move outer cube item into correct subcube
    }

    //! Place new item into subcube based on bounds and inp.data
  }
};


#endif
