// UTIL

#ifndef util_hh
#define util_hh

#include "def.hh"


//------------------------ CONSTANTS ------------------------//

const double PI = atan(1) * 4;
const double PI2 = PI * 2;
const double PID2 = PI / 2;


//------------------------ METHODS ------------------------//

int abs(int a){ return (a < 0) ? -a : a; }
int min(int a, int b){ return (a < b) ? a : b; }
int max(int a, int b){ return (a > b) ? a : b; }

ll absl(ll a){ return (a < 0) ? -a : a; }
ll minl(ll a, ll b){ return (a < b) ? a : b; }
ll maxl(ll a, ll b){ return (a > b) ? a : b; }

double absd(double a){ return (a < 0) ? -a : a; }
double mind(double a, double b){ return (a < b) ? a : b; }
double maxd(double a, double b){ return (a > b) ? a : b; }

void kill(const char* e){
  printf("ERR: %s\n", e);
  exit(1);
}

bool assert(bool b){
  if(!b) kill("Assertion failed");
}


#endif
