#ifndef __DEMO_BALLOON_SHOOTER_AIR_BALLOON_LIB_H__
#define __DEMO_BALLOON_SHOOTER_AIR_BALLOON_LIB_H__

#include "Pokerobo_Lab_Display_Handler.h"

class DemoBalloon {
  public:
    DemoBalloon();
    DemoBalloon(int cx, int cy, int cr);
    void set(GeometryDisplayHandler *displayHandler);
    void check();
    void draw();
  protected:
    void init();
  private:
    int _x;
    int _y;
    int _r;
    GeometryDisplayHandler *_pencil = NULL;
};

DemoBalloon::DemoBalloon() {
  init();
}

DemoBalloon::DemoBalloon(int cx, int cy, int cr) {
  _x = cx; _y = cy; _r = cr;
}

void DemoBalloon::init() {
  _r = random(5, 10 + 1);
  _y = 63 + _r;
  _x = random(0, 128);
}

void DemoBalloon::set(GeometryDisplayHandler *displayHandler) {
  _pencil = displayHandler;
}

void DemoBalloon::check() {
  if (_y + _r >= 0) {
    _y = _y - 3;
  } else {
    _y = 63 + _r;
    _x = random(0, 128);
  }
}

void DemoBalloon::draw() {
  _pencil->drawCircle(_x, _y, _r);
}

#endif
