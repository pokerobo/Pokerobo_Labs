#ifndef __DEMO_BALLOON_SHOOTER_LIB_H__
#define __DEMO_BALLOON_SHOOTER_LIB_H__

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

#define CONCURRENT_BALLOONS_TOTAL 20

class DemoPlaySpace {
  public:
    DemoPlaySpace(GeometryDisplayHandler* pencil,
        uint8_t concurrentTotal=CONCURRENT_BALLOONS_TOTAL);
    void begin();
    void change();
    void draw();
  protected:
    virtual void drawFlyingBalloon(DemoBalloon* balloon);
    void resetBalloon(DemoBalloon* balloon);
  private:
    uint8_t _concurrentTotal = 0;
    DemoBalloon* _balloons[CONCURRENT_BALLOONS_TOTAL];
    GeometryDisplayHandler* _pencil = NULL;
};

#endif
