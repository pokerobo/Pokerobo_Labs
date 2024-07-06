#ifndef __DEMO_BALLOON_SHOOTER_EYE_TARGET_EXT_H__
#define __DEMO_BALLOON_SHOOTER_EYE_TARGET_EXT_H__

#include "Balloon_Shooter-GunTarget-Lib.h"

class DemoSquareGunTarget: public DemoGunTarget {
  public:
    using DemoGunTarget::DemoGunTarget;
    void draw();
  protected:
    virtual void drawBound(int x, int y, int d);
    void drawCross(int x, int y, int d, bool straight=true);
};

class DemoCircleGunTarget: public DemoSquareGunTarget {
  public:
    using DemoSquareGunTarget::DemoSquareGunTarget;
  protected:
    void drawBound(int x, int y, int d);
};

#endif
