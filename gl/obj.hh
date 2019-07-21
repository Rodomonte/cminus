// GL OBJ

#ifndef gl_obj_hh
#define gl_obj_hh

#include "util.hh"


struct Obj : Axis {
  double vel_mag, rot;
  UV vel_dir;
  Obj(P p, UV v): Axis(p, v) {}
  virtual void update() = 0;
  virtual void draw() = 0;
};


struct Scene : Obj {
  int w,h;
  umap<str, Obj>
};


struct Light : Obj {

};


struct Sphere : Obj {

};


struct Cube : Obj {

};


#endif
