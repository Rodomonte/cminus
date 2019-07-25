// GL TEST

#include "../gl/gl.hh"


struct SpinningSphere : Sphere {
  SpinningSphere(){
    y = 20.0;
  }
  void update(){
    xrot(PI/100.0);
  }
};

int main(int argc, char** argv){
  Light a;
  SpinningSphere b;
  gl_start(argv);
  return 0;
}
