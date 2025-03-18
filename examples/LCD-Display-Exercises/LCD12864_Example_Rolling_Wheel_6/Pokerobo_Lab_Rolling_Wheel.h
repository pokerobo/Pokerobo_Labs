#ifndef __POKEROBO_LAB_ROLLING_WHEEL_H__
#define __POKEROBO_LAB_ROLLING_WHEEL_H__

#include "Pokerobo_Lab_Display_Handler.h"

const int halfTotalOfSpokes = 3;
const int totalOfSpokes = 2 * halfTotalOfSpokes;
// 3.14159*360/180/totalOfSpokes
const float angleBetweenSpokes = 3.14159*2/totalOfSpokes;

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
    void begin();
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

#endif
