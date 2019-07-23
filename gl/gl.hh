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
}

void gl_display(){
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  scene.update();
  scene.draw();
  cam.update();
  //glFlush();
  glutSwapBuffers();
  glutPostRedisplay();
}

void gl_configure(char** argv){
  win_w = INIT_WIN_W;
  win_h = INIT_WIN_H;
  cam = Cam();

  int argc = 1;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(win_w, win_h);
  glutInitWindowPosition(400, 1200);
  glutCreateWindow(WIN_TITLE);

  glutDisplayFunc(gl_display);
  glutReshapeFunc(gl_reshape);
  glutMouseFunc(gl_click);
  glutPassiveMotionFunc(gl_motion);
  glutMotionFunc(gl_motion);
  glutKeyboardFunc(gl_key_down);
  glutKeyboardUpFunc(gl_key_up);

  glMatrixMode(GL_PROJECTION);
  gluPerspective(40.0, 1.0, 1.0, 200.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // glEnable(GL_DEPTH_TEST);
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
