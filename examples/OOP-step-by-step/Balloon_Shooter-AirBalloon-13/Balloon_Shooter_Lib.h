#ifndef __DEMO_BALLOON_SHOOTER_LIB_H__
#define __DEMO_BALLOON_SHOOTER_LIB_H__

#include "Pokerobo_Lab_Display_Handler.h"

class DemoBalloon {
  public:
    DemoBalloon() {}
    DemoBalloon(int cx, int cy, int cr) {
      _x = cx; _y = cy; _r = cr;
    }
    void init(GeometryDisplayHandler *displayHandler) {
      _r = random(5, 10 + 1);
      _y = 63 + _r;
      _x = random(0, 128);
      _pencil = displayHandler;
    }
    // method / phương thức / hành vi
    void check() {
      if (_y + _r >= 0) {
        _y = _y - 3;
      } else {
        _y = 63 + _r;
        _x = random(0, 128);
      }
    }
    void draw() {
      _pencil->drawCircle(_x, _y, _r);  
    }
  private:
    // Properties / thuộc tính
    int _x;
    int _y;
    int _r;
    GeometryDisplayHandler *_pencil = NULL;
};

#endif
