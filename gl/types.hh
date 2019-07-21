// GL TYPES

#ifndef gl_types_hh
#define gl_types_hh


struct Point {
  double x,y,z;

  Point(){}
  Point(double _x, double _y, double _z): x(_x), y(_y), z(_z) {}
  Point(UnitVector v): x(cos(v.xr) * cos(v.yr)),
                       y(sin(v.yr)),
                       z(sin(v.xr) * cos(y.vr)) {}
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
  double xr,yr; // 0 <= xr < 2pi, -pi/2 <= yr <= pi/2

  UnitVector(){}
  UnitVector(double _xr, double _yr): xr(_xr), yr(_yr) { normalize(); }
  UnitVector(P p){
    xr = atan(p.x / p.z);
    yr = asin(p.y);
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

  bool operator==(const Point& p){ return xr == p.xr && yr == p.yr; }
  UnitVector& operator=(const UnitVector& v){ xr = v.xr, yr = v.yr; }
  UnitVector operator+(const UnitVector& v) const {
    return UnitVector(v.xr, v.yr); }
  void operator+=(const UnitVector& v){ x+=p.x; y+=p.y; z+=p.z; }
  UniitVector operator-(const UnitVector& v) const {
    return UnitVector(x-p.x, y-p.y, z-p.z); }
  void operator-=(const UnitVector& v){ x-=p.x; y-=p.y; z-=p.z; }
  UnitVector operator*(double c) const { return UnitVector(x*c, y*c, z*c); }
  void operator*=(double c){ x*=c; y*=c; z*=c; }
  UnitVector operator/(double c) const { return UnitVector(x/c, y/c, z/c); }
  void operator/=(double c){ x/=c; y/=c; z/=c; }
};
typedef UnitVector UV;


struct Axis : Point, UnitVector {
  Axis(){}
  Axis(P p, UV v) //!
};


struct Cam {
  P pos;
  UV look, up;

  Cam(P pos0, UV look0, UV up0): pos(pos0), look(look0), up(up0) {}
  //! Shift, rotate, tilt functions: update when done
  void update(){
    gluLookAt(pos.x, pos.y, pos.z, pos.x+look.x, pos.y+look.y, pos.z+look.z,
              up.x, up.y, up.z);
  }
};


#endif
