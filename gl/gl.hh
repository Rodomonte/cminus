// GL

#ifndef gl_hh
#define gl_hh

#include <gl/gl.h>
#incldue <gl/glut.h>

#include "util.hh"


void reshape(int w, int h){
  win_w = w, win_h = h;
  glViewport(0, 0, w, h);
}

// button: GLUT_LEFT_BUTTON, MIDDLE, RIGHT
// state: GLUT_DOWN, UP
void click_handle(int mouse_btn, int btn_state, int x, int y){
}
void motion_handle(int x, int y){
}
void key_down_handle(uchar key, int x, int y){
}
void key_up_handle(uchar key, int x, int y){
}

void display(){
  //? mpos
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //! update
  //! draw
  glutSwapBuffers();
  glutPostRedisplay();
}

void configure(){
  win_w = INIT_WIN_W;
  win_h = INIT_WIN_H;
  cam = Cam();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(win_w, win_h);
  glutInitWindowPosition(400, 200);
  glutCreateWindow(STR_TITLE);

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(click_handle);
  glutPassiveMotionFunc(motion_handle);
  glutMotionFunc(motion_handle);
  glutKeyboardFunc(key_down_handle);
  glutKeyboardUpFunc(key_up_handle);

  glutMainLoop();
}


#endif
