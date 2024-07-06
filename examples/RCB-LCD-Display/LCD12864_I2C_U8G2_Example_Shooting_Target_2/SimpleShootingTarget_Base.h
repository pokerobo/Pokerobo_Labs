#ifndef __POKEROBO_LAB_SHOOTING_TARGET_2_BASE_H__
#define __POKEROBO_LAB_SHOOTING_TARGET_2_BASE_H__

#include <Pokerobo_RCB.h>
#include "Pokerobo_Lab_Display_Handler.h"

class SimpleShootingTarget {
  public:
    SimpleShootingTarget(GeometryDisplayHandler *displayHandler);
    void draw();
    int8_t speedOfX(uint16_t x);
    int8_t speedOfY(uint16_t y);
    int8_t moveX(int8_t joyX);
    int8_t moveY(int8_t joyY);
  protected:
    void drawPlus(int8_t x, int8_t y, int8_t d);
    int8_t _x;
    int8_t _y;
    GeometryDisplayHandler *_pencil;
};

SimpleShootingTarget::SimpleShootingTarget(GeometryDisplayHandler *displayHandler) {
  _pencil = displayHandler;
  _x = 63;
  _y = 31;
}

void SimpleShootingTarget::draw() {
  drawPlus(_x, _y, 3);
}

void SimpleShootingTarget::drawPlus(int8_t x, int8_t y, int8_t d) {
  int8_t x1 = (x-d >= 0) ? x-d : 0;
  int8_t x2 = (x+d <= 127) ? x+d : 127;
  int8_t y1 = (y-d >= 0) ? y-d : 0;
  int8_t y2 = (y+d <= 63) ? y+d : 63;
  _pencil->drawLine(x1, y, x2, y);
  _pencil->drawLine(x, y1, x, y2);
}

int8_t SimpleShootingTarget::speedOfX(uint16_t x) {
  int jX = -512 + x;

  Serial.print("jX: "), Serial.print(jX);
  Serial.print(" -> ");

  if (-30 < jX && jX < 30) {
    jX = 0;
  }

  int rX = map(jX, -512, 512, -5, 5);

  Serial.print("rX: "), Serial.print(rX);
  Serial.println();

  return rX;
}

int8_t SimpleShootingTarget::speedOfY(uint16_t y) {
  int jY = -512 + y;

  Serial.print("jY: "), Serial.print(jY);
  Serial.print(" -> ");

  if (-30 < jY && jY < 30) {
    jY = 0;
  }

  int rY = map(jY, -512, 512, 5, -5);

  Serial.print("rY: "), Serial.print(rY);
  Serial.println();

  return rY;
}

int8_t SimpleShootingTarget::moveX(int8_t dX) {
  int8_t oX = _x;
  if (dX < 0 && _x < -dX) {
    _x = 0;
  } else if (dX > 0 && _x > 127 - dX) {
    _x = 127;
  } else {
    _x = _x + dX;
  }
  return _x - oX;
}

int8_t SimpleShootingTarget::moveY(int8_t dY) {
  int8_t oY = _y;
  if (_y < -dY) {
    _y = 0;
  } else if (_y > 63 - dY) {
    _y = 63;
  } else {
    _y = _y + dY;
  }
  return _y - oY;
}

#endif
