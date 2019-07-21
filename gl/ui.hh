// GL UI

#ifndef gl_ui_hh
#define gl_ui_hh

#include "../core/str.hh"
#include "obj.hh"


struct Button : Obj {
  enum ButtonState {
    UP,
    HOVER,
    DOWN
  } state ;
  int w, h;
  str label;

  Button(): state(UP) {}
  Button(P p, int _w, int _h, str& _label):
      Obj(p, UV(PI, 0)), state(UP), w(_w), h(_h), label(_label) {}

  bool contains(P p){
    return (p.x >= x && p.x < x+w && p.y >= y && p.y < y+h);
  }
  void click(int mouse_btn, int btn_state){
    if(mouse_btn != GLUT_LEFT_BUTTON) return;
    if(btn_state == GLUT_DOWN && state == HOVER) state = DOWN;
    else if(btn_state == GLUT_UP && state == DOWN) state = UP, action();
  }
  void motion(){ if(state == UP) state = HOVER; }

  virtual void action() = 0;
};


#endif
