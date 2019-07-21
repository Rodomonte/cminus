// GL UTIL

#ifndef gl_util_hh
#define gl_util_hh

#include "types.hh"


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
