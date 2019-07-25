// GL

#ifndef gl_hh
#define gl_hh

#include "util.hh"


void gl_start(char** argv){
  win_w = INIT_WIN_W;
  win_h = INIT_WIN_H;
  cam = Cam();

  sf::RenderWindow _win(sf::VideoMode(win_w, win_h), WIN_TITLE);
  win = &_win;

  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);

  glEnable(GL_LIGHT0);
  float white[] = {1.0, 1.0, 1.0, 1.0};
  float pos[] = {0.0, 100.0, 0.0, 0.0};
  glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT0, GL_POSITION, pos);

  sf::Event event;
  while(_win.isOpen()){
    while(_win.pollEvent(event)){
      if(event.type == sf::Event::Closed)
        _win.close();
      if(event.type == sf::Event::Resized){
        win_w = event.size.width;
        win_h = event.size.height;
        sf::FloatRect area(0, 0, win_w, win_h);
        _win.setView(sf::View(area));
      }
    }
    _win.clear();

    cam.update();
    scene.update();
    scene.draw();
    _win.display();
  }
}


#endif
