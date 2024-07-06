#ifndef __DEMO_BALLOON_SHOOTER_LIB_H__
#define __DEMO_BALLOON_SHOOTER_LIB_H__

#include "Pokerobo_Lab_Display_Handler.h"

typedef enum BALLOON_STATE {
  BALLOON_NEW = 0,
  BALLOON_FLYING,
  BALLOON_EXPLODED,
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
    bool isHit(int8_t aimX, int8_t aimY);
  private:
    balloon_state_t _s = BALLOON_STATE::BALLOON_NEW;
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
    int8_t prick(int8_t aimX, int8_t aimY);
  protected:
    void initBalloon(DemoBalloon* balloon);
    void resetBalloon(DemoBalloon* balloon);
    virtual void drawExplodingBalloon(DemoBalloon* balloon);
    virtual void drawFlyingBalloon(DemoBalloon* balloon);
  private:
    uint8_t _concurrentTotal = 0;
    DemoBalloon* _balloons[CONCURRENT_BALLOONS_TOTAL];
    GeometryDisplayHandler* _pencil = NULL;
};

#endif
