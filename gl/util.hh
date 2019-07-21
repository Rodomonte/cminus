// GL UTIL

#ifndef gl_util_hh
#define gl_util_hh

#include "../core/util.hh"


//------------------------ TYPES ------------------------//

struct Point {
  double x,y,z;

  Point(){}
  Point(const Point& p): x(p.x), y(p.y), z(p.z) {}
  Point(double _x, double _y, double _z): x(_x), y(_y), z(_z) {}
  double len(){ return sqrt(x*x + y*y + z*z); }

  bool operator==(const Point& p){ return x == p.x && y == p.y && z == p.z; }
  Point& operator=(const Point& p){ x = p.x, y = p.y, z = p.z; }
  Point operator+(const Point& p) const { return Point(x+p.x, y+p.y, z+p.z); }
  void operator+=(const Point& p){ x+=p.x; y+=p.y; z+=p.z; }
  Point operator-(const Point& p) const { return Point(x-p.x, y-p.y, z-p.z); }
  void operator-=(const Point& p){ x-=p.x; y-=p.y; z-=p.z; }
  Point operator*(double c) const { return Point(x*c, y*c, z*c); }
  void operator*=(double c){ x*=c; y*=c; z*=c; }
  Point operator/(double c) const { return Point(x/c, y/c, z/c); }
  void operator/=(double c){ x/=c; y/=c; z/=c; }
};
typedef Point P;


struct UnitVector {
  double xr,yr; // 0 <= xr < 2PI, -PI/2 <= yr <= PI/2

  UnitVector(){}
  UnitVector(const UnitVector& v): xr(v.xr), yr(v.yr) {}
  UnitVector(double _xr, double _yr): xr(_xr), yr(_yr) { normalize(); }

  UnitVector(P p){
    xr = atan(p.x / p.z);
    yr = asin(p.y);
  }
  P point(){
    return P(cos(xr) * cos(yr), sin(yr), sin(xr) * cos(yr));
  }

  void normalize(){ //! Does fmod handle negatives?
    xr = fmod(xr, PI2);
    yr = fmod(yr + PID2, PI2) - PID2;
    if(yr > PID2){
      xr += PI;
      yr = PI - yr;
      normalize();
    }
  }

  bool operator==(const UnitVector& v){ return xr == v.xr && yr == v.yr; }
  UnitVector& operator=(const UnitVector& v){ xr = v.xr, yr = v.yr; }
};
typedef UnitVector UV;


struct Axis : P, UV {
  Axis(){}
  Axis(P p, UV v): P(p), UV(v) {}
};


//! Cam : Axis
struct Cam : Axis {
  double xr;

  Cam(): Axis(P(0, 0, -100), UV(0, 0)), xr(0) {}
  void update(){
    // P _look(look), _up(up);
    // gluLookAt(pos.x, pos.y, pos.z, pos.x+_look.x, pos.y+_look.y, pos.z+_look.z,
    //           _up.x, _up.y, _up.z);
  }
  //! Shift, rotate, tilt
};


//------------------------ CONSTANTS ------------------------//

const int INIT_WIN_W = 800;
const int INIT_WIN_H = 600;
const char* WIN_TITLE = "GL";


//------------------------ GLOBALS ------------------------//

int win_w, win_h;
P mpos;
Cam cam;


//------------------------ METHODS ------------------------//

void prep2d(){
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, win_w, win_h, 0, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void prep3d(){
  glEnable(GL_DEPTH_TEST);
  //glColorMaterial(GL_FRONT, GL_AMBIENT);
  glColorMaterial(GL_FRONT, GL_DIFFUSE);
  //glColorMaterial(GL_FRONT, GL_SPECULAR);
  glEnable(GL_COLOR_MATERIAL);

  float light_pos[] = {-1, -1, -1, 0};
  float light_amb[] = {0, 0, 0, 1};
  float light_diff[] = {1, 1, 1, 1};
  float light_spec[] = {1, 1, 1, 1};
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  //glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);
  //glLightfv(GL_LIGHT0, GL_SPECULAR, light_spec);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //gluPerspective(45, (double)win_w/win_h, 1, 10000);
  //cam->update();
  glOrtho(0, win_w, win_h, 0, -10000, 10000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


#endif
