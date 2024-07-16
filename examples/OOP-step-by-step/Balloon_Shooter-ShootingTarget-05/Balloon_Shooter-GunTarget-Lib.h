#ifndef __DEMO_BALLOON_SHOOTER_EYE_TARGET_LIB_H__
#define __DEMO_BALLOON_SHOOTER_EYE_TARGET_LIB_H__

#include "Pokerobo_Lab_Display_Handler.h"

class DemoGunTarget {
  public:
    DemoGunTarget(GeometryDisplayHandler* displayHandler);

    int getX();
    int getY();

    int speedOfX(int jX);
    int speedOfY(int jY);

    void move(int dX, int dY);
    void update(int jX, int jY);
    void draw();

  private:
    int x;
    int y;
    int r = 3;
    GeometryDisplayHandler* _pencil;
};

#endif
