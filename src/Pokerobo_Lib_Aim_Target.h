#ifndef __POKEROBO_LIB_AIM_TARGET_H__
#define __POKEROBO_LIB_AIM_TARGET_H__

#include "Pokerobo_Lib_Display_Layout.h"

class AimTarget {
  public:
    AimTarget(CoordinateAxes* axes, byte type=0xFF);
    void render();
    int8_t speedOfX(uint16_t x, uint16_t y);
    int8_t speedOfY(uint16_t x, uint16_t y);
    int8_t moveX(int8_t deltaX);
    int8_t moveY(int8_t deltaY);
    int8_t getX();
    int8_t getY();
  private:
    void drawPlus(int8_t x, int8_t y, int8_t d);
    byte _type;
    int8_t x;
    int8_t y;
    CoordinateAxes* _axes;
};

#endif
