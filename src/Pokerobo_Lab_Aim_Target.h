#ifndef __POKEROBO_LAB_AIM_TARGET_H__
#define __POKEROBO_LAB_AIM_TARGET_H__

#include "Pokerobo_Lab_Display_Handler.h"
#include "Pokerobo_Lab_Display_Layout.h"

class AimTarget {
  public:
    AimTarget(GeometryDisplayHandler* pencil, byte type=0xFF);
    AimTarget(CoordinateAxes* axes, byte type=0xFF);
    void moveByJoystick(uint16_t x, uint16_t y);
    int8_t speedOfX(uint16_t x, uint16_t y);
    int8_t speedOfY(uint16_t x, uint16_t y);
    int8_t moveX(int8_t deltaX);
    int8_t moveY(int8_t deltaY);
    int8_t getX();
    int8_t getY();
    virtual void draw();
  protected:
    void initialize(byte type);
    CoordinateAxes* getCoordinateAxes();
    GeometryDisplayHandler* getPencil();
    void drawCross(int8_t x, int8_t y, int8_t d=2, bool straight=true);
  private:
    byte _type;
    int8_t x;
    int8_t y;
    CoordinateAxes* _axes = NULL;
    GeometryDisplayHandler* _pencil = NULL;
};

#endif
