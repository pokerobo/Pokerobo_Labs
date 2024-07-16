#ifndef __DEMO_BALLOON_SHOOTER_EYE_TARGET_LIB_H__
#define __DEMO_BALLOON_SHOOTER_EYE_TARGET_LIB_H__

#include "Pokerobo_Lab_Display_Handler.h"

class DemoGunTarget {
  public:
    DemoGunTarget(GeometryDisplayHandler* displayHandler) {
      _pencil = displayHandler;
    }

    int getX() { return x; }
    int getY() { return y; }

    int speedOfX(int jX) {
      int dX = -512 + jX; // jX - 512
      if (abs(dX) < 30) dX = 0;
      return map(dX, -512, 512, -10, 10);
    }

    int speedOfY(int jY) {
      int dY = -512 + jY; // jY - 512
      if (abs(dY) < 30) dY = 0;
      return map(dY, -512, 512, 10, -10);
    }

    void move(int dX, int dY) {
      int _maxX = _pencil->getMaxX();
      int _maxY = _pencil->getMaxY();
      x = x + dX > 0 ? (x + dX <= _maxX ? x + dX : _maxX) : 0;
      y = y + dY > 0 ? (y + dY <= _maxY ? y + dY : _maxY) : 0;
    }

    void update(int jX, int jY) {
      move(speedOfX(jX), speedOfY(jY));
    }

    void draw() {
      _pencil->drawPixel(x, y);
      _pencil->drawCircle(x, y, r);
    }
  private:
    int x;
    int y;
    int r = 3;
    GeometryDisplayHandler* _pencil;
};

#endif
