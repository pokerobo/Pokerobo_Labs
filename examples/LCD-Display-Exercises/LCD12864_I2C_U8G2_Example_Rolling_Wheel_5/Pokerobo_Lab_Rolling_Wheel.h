#ifndef __POKEROBO_LAB_ROLLING_WHEEL_H__
#define __POKEROBO_LAB_ROLLING_WHEEL_H__

#include "Pokerobo_Lab_Display_Handler.h"

const int halfTotalOfSpokes = 3;
const int totalOfSpokes = 2 * halfTotalOfSpokes;
const float angleBetweenSpokes = 3.14159*360/180/totalOfSpokes;

class Spoke {
  friend class Wheel;
  private:
    int no;
    int x;
    int y;
};

class Wheel {
  public:
    Wheel(GeometryDisplayHandler *displayHandler);
    void roll(int speed, byte direction);
    void swing(int speed, byte &direction);
    void draw();
  private:
    int r = 15;
    int x = 0;
    int y = 0;
    float diameter = 0.0;
    float distance = 0.0;
    Spoke *spokes[totalOfSpokes];
    GeometryDisplayHandler *_displayHandler;
};

Wheel::Wheel(GeometryDisplayHandler *displayHandler) {
  _displayHandler = displayHandler;
  x = r;
  y = _displayHandler->getMaxY() - r;
  diameter = PI * r * 2;
  for(int i=0; i<totalOfSpokes; i++) {
    spokes[i] = new Spoke();
  }
};

void Wheel::roll(int speed, byte direction) {
  int maxX = _displayHandler->getMaxX();
  if (direction) {
    if (x < maxX - r) {
      x = x + speed;
    }
    while (x > maxX - r) {
      x = maxX - r;
    }
    distance = distance + speed;
    while (distance >= diameter) {
      distance = distance - diameter;
    }
  } else {
    if (x > r) {
      x = x - speed;
    }
    if (x < r) {
      x = r;
    }
    distance = distance - speed;
    while (distance < 0.0) {
      distance = distance + diameter;
    }
  }
  for(int i=0; i<halfTotalOfSpokes; i++) {
    Spoke *s1 = spokes[i];
    float angle = i*angleBetweenSpokes + distance/r;
    s1->x = x + r*cos(angle);
    s1->y = y + r*sin(angle);
    Spoke *s2 = spokes[halfTotalOfSpokes + i];
    s2->x = 2*x - s1->x;
    s2->y = 2*y - s1->y;
  }
};

void Wheel::swing(int speed, byte &direction) {
  roll(speed, direction);
  int maxX = _displayHandler->getMaxX();
  if (direction) {
    if (x == maxX - r) {
      direction = 1 - direction;
    }
  } else {
    if (x == r) {
      direction = 1 - direction;
    }
  }
}

void Wheel::draw() {
  _displayHandler->drawCircle(x, y, r);
  _displayHandler->drawCircle(x, y, 2);
  for(int i=0; i<totalOfSpokes; i++) {
    Spoke *spoke = spokes[i];
    _displayHandler->drawLine(x, y, spoke->x, spoke->y);
  }
};

#endif
