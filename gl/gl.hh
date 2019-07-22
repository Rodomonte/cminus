// GL

#ifndef gl_hh
#define gl_hh

#include <gl/gl.h>
#include <gl/glut.h>
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
  //! scene update
  //! scene draw
  glutSwapBuffers();
  glutPostRedisplay();
}

void gl_configure(char** argv){
  win_w = INIT_WIN_W;
  win_h = INIT_WIN_H;
  cam = Cam();

  int argc = 1;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(win_w, win_h);
  glutInitWindowPosition(400, 200);
  glutCreateWindow(WIN_TITLE);

  glutDisplayFunc(gl_display);
  glutReshapeFunc(gl_reshape);
  glutMouseFunc(gl_click);
  glutPassiveMotionFunc(gl_motion);
  glutMotionFunc(gl_motion);
  glutKeyboardFunc(gl_key_down);
  glutKeyboardUpFunc(gl_key_up);

  glutMainLoop();
}


#endif
