// GLB

#ifndef glb_hh
#define glb_hh

#include "util.hh"
#include "vec.hh"


// CONSTANTS

const ll MAX_RAM    = 0  //!
       , THREAD_TTL = 0; //!


// BUFFERS

char buf[10485760];


// HEAP //! no vector?

struct stat;
vec<stat> cl_stat;

struct stamp;
vec<stamp> cl_stamp;

struct mem;
vec<mem> cl_mem;

struct num;
vec<num> cl_num;

struct frac;
vec<frac> cl_frac;

struct cube;
vec<cube> cl_cube;

struct Thing;
vec<Thing> cl_thing;


#endif
