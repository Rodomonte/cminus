// MATH

#ifndef math_hh
#define math_hh

#define TRIG_ITER = 20;


double _atan(double a);
const double PI = _atan(1.0) * 4.0;
const double PI2 = PI * 2.0;
const double PID2 = PI / 2.0;


template<class T>
T min(const T& a, const T& b){ return (a < b) ? a : b; }
//!


double _sin(double a){
  int i;
  double f,p,r;
  r = 0.0;
  for(i = 0; i < TRIG_ITER; ++i){
    f = p = 1.0;

  }
  return r;
}

double _cos(double a){

}

double _tan(double a){

}

double _asin(double a){

}

double _acos(double a){

}

double _atan(double a){

}


#endif
