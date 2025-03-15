#ifndef __DEMO_BALLOON_SHOOTER_PLAY_SPACE_LIB_H__
#define __DEMO_BALLOON_SHOOTER_PLAY_SPACE_LIB_H__

#include "Balloon_Shooter-AirBalloon-Lib.h"

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
