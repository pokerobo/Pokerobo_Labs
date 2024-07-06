#ifndef __DEMO_BALLOON_SHOOTER_EYE_TARGET_LIB_H__
#define __DEMO_BALLOON_SHOOTER_EYE_TARGET_LIB_H__

#include "Pokerobo_Lab_Display_Handler.h"

class DemoGunTarget {
  public:
    DemoGunTarget(GeometryDisplayHandler* displayHandler, byte speed=10);

    int getX();
    int getY();

    void move(int dX, int dY);
    void update(int jX, int jY);
    void draw();

  protected:
    int speedOfX(int jX, int jY);
    int speedOfY(int jX, int jY);
    GeometryDisplayHandler* getPencil();
  private:
    int x;
    int y;
    int r = 3;
    byte _speed = 10;
    GeometryDisplayHandler* _pencil;
};

#endif
