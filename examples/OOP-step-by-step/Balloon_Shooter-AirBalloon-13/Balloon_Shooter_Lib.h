#ifndef __DEMO_BALLOON_SHOOTER_LIB_H__
#define __DEMO_BALLOON_SHOOTER_LIB_H__

#include "Pokerobo_Lab_Display_Handler.h"

class DemoBalloon {
  public:
    // Constructors
    DemoBalloon() { init(); }
    DemoBalloon(int cx, int cy, int cr) {
      _x = cx; _y = cy; _r = cr;
    }
    void set(GeometryDisplayHandler *displayHandler) {
      _pencil = displayHandler;
    }
    // Methods
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
  protected:
    void init() {
      _r = random(5, 10 + 1);
      _y = 63 + _r;
      _x = random(0, 128);
    }
  private:
    // Properties
    int _x;
    int _y;
    int _r;
    GeometryDisplayHandler *_pencil = NULL;
};

#endif
