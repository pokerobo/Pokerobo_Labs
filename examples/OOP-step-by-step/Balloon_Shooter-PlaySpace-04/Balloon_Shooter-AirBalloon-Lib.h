#ifndef __DEMO_BALLOON_SHOOTER_AIR_BALLOON_LIB_H__
#define __DEMO_BALLOON_SHOOTER_AIR_BALLOON_LIB_H__

#include "Pokerobo_Lab_Display_Handler.h"

typedef enum BALLOON_STATE {
  BALLOON_NEW = 0,
  BALLOON_FLYING,
  BALLOON_ESCAPED,
} balloon_state_t;

class DemoBalloon {
  friend class DemoPlaySpace;
  public:
    DemoBalloon();
    DemoBalloon(int cx, int cy, int cr);
    int getX();
    int getY();
    int8_t getRadius();
    int8_t getSpeed();
    bool isEscaped();
  private:
    balloon_state_t _s = BALLOON_STATE::BALLOON_NEW;
    int _x;
    int _y;
    int _r;
};

#endif
