#ifndef __DEMO_BALLOON_SHOOTER_LIB_H__
#define __DEMO_BALLOON_SHOOTER_LIB_H__

#include "Pokerobo_Lab_Display_Handler.h"

class DemoBalloon {
  public:
    DemoBalloon();
    DemoBalloon(int cx, int cy, int cr);
    void init(GeometryDisplayHandler *displayHandler);
    void check();
    void draw();
  private:
    int _x;
    int _y;
    int _r;
    GeometryDisplayHandler *_pencil = NULL;
};

#endif
