// CUBE
//! Test: Each adj's adj is itself

#ifndef cube_hh
#define cube_hh

#include "glb.hh"
#include "util.hh"


//! Adjust logic to include this
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
  bool set;
  double data[3];
  item(){}
  item(double x, double y, double z):
    data[X](x), data[Y](y), data[Z](z) {}
  void clear(){
    set = false, data[0] = data[1] = data[2] = 0.0;
  }
};

//! hash item as map key -> containing subcube
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
        lbd[i] = mind(t.data[i], lbd[i]),
        ubd[i] = maxd(t.data[i], ubd[i]);
    for(item& t : v)
      insert(t);
  }

  // Insert one item into cube
  void insert(item& inp){
    int i;
    // If no items in cube, place into outer cube
    if(!val.data.set && ntr[TNW] == NULL){
      val = inp;
      return;
    }

    // Subdivide into 8 interior cubes, moving val
    if(ntr[TNW] == NULL){
      place(val);
      val.clear();
    }

    // Place input item into subcube
    place(inp);
  }

  // Place item into appropriate subcube
  void place(item& inp){
    if(ntr[TNW] == NULL)
      subdivide();

    // Recurse into appropriate subcube
    if(val.data[X] <= ntr[TNW]->ubd[X]){
      if(val.data[Y] <= ntr[TNW]->ubd[Y]){

      }else if(val.data[Z] <= ntr[TNW]->ubd[Z]){

      }else
        ntr[BSW]->val = val; //!
    }else if(val.data[Y] <= ntr[TNW]->ubd[Y]){

    }else if(val.data[Z] <= ntr[TNW]->ubd[Z]){

    }else
      ntr[BSE]->val = val; //!
  }

  // Create 8 subcubes within cube
  void subdivide(){
    int i;
    double hx, hy, hz;
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
    hx = lbd[X] + (ubd[X] - lbd[X]) / 2.0;
    hy = lbd[Y] + (ubd[Y] - lbd[Y]) / 2.0;
    hz = lbd[Z] + (ubd[Z] - lbd[Z]) / 2.0;

    ntr[TNW]->lbd[X] = ntr[TSW]->lbd[X] = lbd[X];
    ntr[BNW]->lbd[X] = ntr[BSW]->lbd[X] = lbd[X];
    ntr[TNW]->lbd[Y] = ntr[TNE]->lbd[Y] = lbd[Y];
    ntr[BNW]->lbd[Y] = ntr[BNE]->lbd[Y] = lbd[Y];
    ntr[TNW]->lbd[Z] = ntr[TNE]->lbd[Z] = lbd[Z];
    ntr[TSW]->lbd[Z] = ntr[TSE]->lbd[Z] = lbd[Z];

    ntr[TNW]->ubd[X] = ntr[TSW]->ubd[X] = hx;
    ntr[BNW]->ubd[X] = ntr[BSW]->ubd[X] = hx;
    ntr[TNW]->ubd[Y] = ntr[TNE]->ubd[Y] = hy;
    ntr[BNW]->ubd[Y] = ntr[BNE]->ubd[Y] = hy;
    ntr[TNW]->ubd[Z] = ntr[TNE]->ubd[Z] = hz;
    ntr[TSW]->ubd[Z] = ntr[TSE]->ubd[Z] = hz;

    ntr[TNE]->lbd[X] = ntr[TSE]->lbd[X] = hx;
    ntr[BNE]->lbd[X] = ntr[BSE]->lbd[X] = hx;
    ntr[TSW]->lbd[Y] = ntr[TSE]->lbd[Y] = hy;
    ntr[BSW]->lbd[Y] = ntr[BSE]->lbd[Y] = hy;
    ntr[BNW]->lbd[Z] = ntr[BNE]->lbd[Z] = hz;
    ntr[BSW]->lbd[Z] = ntr[BSE]->lbd[Z] = hz;

    ntr[TNE]->ubd[X] = ntr[TSE]->ubd[X] = ubd[X];
    ntr[BNE]->ubd[X] = ntr[BSE]->ubd[X] = ubd[X];
    ntr[TSE]->ubd[Y] = ntr[TSW]->ubd[Y] = ubd[Y];
    ntr[BSE]->ubd[Y] = ntr[BSW]->ubd[Y] = ubd[Y];
    ntr[BNW]->ubd[Z] = ntr[BNE]->ubd[Z] = ubd[Z];
    ntr[BSW]->ubd[Z] = ntr[BSE]->ubd[Z] = ubd[Z];

    // Link adjacent cubes
    if(adj[T] != NULL){
      if(adj[T]->ntr[TNW] == NULL){
        ntr[TNW]->adj[T] = ntr[TNE]->adj[T] = adj[T];
        ntr[TSW]->adj[T] = ntr[TSE]->adj[T] = adj[T];
      }else{
        ntr[TNW]->adj[T] = adj[T]->ntr[BNW];
        ntr[TNW]->adj[T]->adj[B] = ntr[TNW];
        ntr[TNE]->adj[T] = adj[T]->ntr[BNE];
        ntr[TNE]->adj[T]->adj[B] = ntr[TNE];
        ntr[TSW]->adj[T] = adj[T]->ntr[BSW];
        ntr[TSW]->adj[T]->adj[B] = ntr[TSW];
        ntr[TSE]->adj[T] = adj[T]->ntr[BSE];
        ntr[TSE]->adj[T]->adj[B] = ntr[TSE];
      }
    }

    if(adj[N] != NULL){
      if(adj[N]->ntr[TNW] == NULL){
        ntr[TNW]->adj[N] = ntr[TNE]->adj[N] = adj[N];
        ntr[BNW]->adj[N] = ntr[BNE]->adj[N] = adj[N];
      }else{
        ntr[TNW]->adj[N] = adj[N]->ntr[TSW];
        ntr[TNW]->adj[N]->adj[S] = ntr[TNW];
        ntr[TNE]->adj[N] = adj[N]->ntr[TSE];
        ntr[TNE]->adj[N]->adj[S] = ntr[TNE];
        ntr[BNW]->adj[N] = adj[N]->ntr[BSW];
        ntr[BNW]->adj[N]->adj[S] = ntr[BNW];
        ntr[BNE]->adj[N] = adj[N]->ntr[BSE];
        ntr[BNE]->adj[N]->adj[S] = ntr[BNE];
      }
    }

    if(adj[E] != NULL){
      if(adj[E]->ntr[TNW] == NULL){
        ntr[TNE]->adj[E] = ntr[TSE]->adj[E] = adj[E];
        ntr[BNE]->adj[E] = ntr[BSE]->adj[E] = adj[E];
      }else{
        ntr[TNE]->adj[E] = adj[E]->ntr[TNW];
        ntr[TNE]->adj[E]->adj[W] = ntr[TNE];
        ntr[TSE]->adj[E] = adj[E]->ntr[TSW];
        ntr[TSE]->adj[E]->adj[W] = ntr[TSE];
        ntr[BNE]->adj[E] = adj[E]->ntr[BNW];
        ntr[BNE]->adj[E]->adj[W] = ntr[BNE];
        ntr[BSE]->adj[E] = adj[E]->ntr[BSW];
        ntr[BSE]->adj[E]->adj[W] = ntr[BSE];
      }
    }

    if(adj[S] != NULL){
      if(adj[S]->ntr[TNW] == NULL){
        ntr[TSW]->adj[S] = ntr[TSE]->adj[S] = adj[S];
        ntr[BSW]->adj[S] = ntr[BSE]->adj[S] = adj[S];
      }else{
        ntr[TSW]->adj[S] = adj[S]->ntr[TNW];
        ntr[TSW]->adj[S]->adj[N] = ntr[TSW];
        ntr[TSE]->adj[S] = adj[S]->ntr[TNE];
        ntr[TSE]->adj[S]->adj[N] = ntr[TSE];
        ntr[BSW]->adj[S] = adj[S]->ntr[BNW];
        ntr[BSW]->adj[S]->adj[N] = ntr[BSW];
        ntr[BSE]->adj[S] = adj[S]->ntr[BNE];
        ntr[BSE]->adj[S]->adj[N] = ntr[BSE];
      }
    }

    if(adj[W] != NULL){
      if(adj[W]->ntr[TNW] == NULL){
        ntr[TNW]->adj[W] = ntr[TSW]->adj[W] = adj[W];
        ntr[BNW]->adj[W] = ntr[BSW]->adj[W] = adj[W];
      }else{
        ntr[TNW]->adj[W] = adj[W]->ntr[TNE];
        ntr[TNW]->adj[W]->adj[E] = ntr[TNW];
        ntr[TSW]->adj[W] = adj[W]->ntr[TSE];
        ntr[TSW]->adj[W]->adj[E] = ntr[TSW];
        ntr[BNW]->adj[W] = adj[W]->ntr[BNE];
        ntr[BNW]->adj[W]->adj[E] = ntr[BNW];
        ntr[BSW]->adj[W] = adj[W]->ntr[BSE];
        ntr[BSW]->adj[W]->adj[E] = ntr[BSE];
      }
    }

    if(adj[B] != NULL){
      if(adj[B]->ntr[TNW] == NULL){
        ntr[BNW]->adj[B] = ntr[BNE]->adj[B] = adj[B];
        ntr[BSW]->adj[B] = ntr[BSE]->adj[B] = adj[B];
      }else{
        ntr[BNW]->adj[B] = adj[B]->ntr[TNW];
        ntr[BNW]->adj[B]->adj[T] = ntr[BNW];
        ntr[BNE]->adj[B] = adj[B]->ntr[TNE];
        ntr[BNE]->adj[B]->adj[T] = ntr[BNE];
        ntr[BSW]->adj[B] = adj[B]->ntr[TSW];
        ntr[BSW]->adj[B]->adj[T] = ntr[BSW];
        ntr[BSE]->adj[B] = adj[B]->ntr[TSE];
        ntr[BSE]->adj[B]->adj[T] = ntr[BSE];
      }
    }
  }
};


#endif
