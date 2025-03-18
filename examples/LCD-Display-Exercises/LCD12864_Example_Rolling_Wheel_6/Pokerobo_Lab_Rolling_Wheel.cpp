#include "Pokerobo_Lab_Rolling_Wheel.h"

Wheel::Wheel(GeometryDisplayHandler *displayHandler) {
  _displayHandler = displayHandler;
  x = r;
  y = _displayHandler->getMaxY() - r;
  diameter = PI * r * 2;
  for(int i=0; i<totalOfSpokes; i++) {
    spokes[i] = new Spoke();
  }
};

void Wheel::begin() {
  roll(0, 0);
}

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
