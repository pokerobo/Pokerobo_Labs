#ifndef __DEMO_BALLOON_SHOOTER_AIR_BALLOON_LIB_H__
#define __DEMO_BALLOON_SHOOTER_AIR_BALLOON_LIB_H__

#include "Pokerobo_Lab_Display_Handler.h"

class DemoBalloon {
  friend class DemoPlaySpace;
  public:
    DemoBalloon();
    DemoBalloon(int cx, int cy, int cr);
  private:
    int _x;
    int _y;
    int _r;
};

#endif
