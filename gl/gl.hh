// GL

#ifndef gl_hh
#define gl_hh

#include <GL/gl.h>
#include <GL/glut.h>
//#include <sfml/graphics.hpp>

#include "util.hh"


// button: GLUT_LEFT_BUTTON, MIDDLE, RIGHT
// state: GLUT_DOWN, UP
void gl_click(int mouse_btn, int btn_state, int x, int y){
}
void gl_motion(int x, int y){
  mpos.x = x, mpos.y = y;
}
void gl_key_down(uchar key, int x, int y){
}
void gl_key_up(uchar key, int x, int y){
}

void gl_reshape(int w, int h){
  win_w = w, win_h = h;
  glViewport(0, 0, w, h);
  const float ar = (float)w / (float)h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void gl_display(){
  printf("display called\n");
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  cam.update();
  scene.update();
  scene.draw();
  glutSwapBuffers();
  glutPostRedisplay();
}

void gl_start(char** argv){
  win_w = INIT_WIN_W;
  win_h = INIT_WIN_H;
  cam = Cam();

  int argc = 1;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(win_w, win_h);
  glutInitWindowPosition(200, 200);
  glutCreateWindow(WIN_TITLE);

  glutDisplayFunc(gl_display);
  glutReshapeFunc(gl_reshape);
  glutMouseFunc(gl_click);
  glutPassiveMotionFunc(gl_motion);
  glutMotionFunc(gl_motion);
  glutKeyboardFunc(gl_key_down);
  glutKeyboardUpFunc(gl_key_up);

  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);

  glEnable(GL_LIGHT0);
  float white[] = {1.0, 1.0, 1.0, 1.0};
  float pos[] = {0.0, 100.0, 0.0, 0.0};
  glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT0, GL_POSITION, pos);

  glutMainLoop();
}


#endif
