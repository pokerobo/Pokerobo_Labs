#ifndef __POKEROBO_LAB_SHOOTING_TARGET_2_EXTENSION_H__
#define __POKEROBO_LAB_SHOOTING_TARGET_2_EXTENSION_H__

#include "SimpleShootingTarget_Base.h"

class SimpleShootingTargetInSquare: public SimpleShootingTarget {
  public:
    using SimpleShootingTarget::SimpleShootingTarget;
    void draw();
};

void SimpleShootingTargetInSquare::draw() {
  drawPlus(_x, _y, 4);
  _pencil->drawFrame(_x-3, _y-3, 7, 7);
}

class SimpleShootingTargetInCircle: public SimpleShootingTarget {
  public:
    using SimpleShootingTarget::SimpleShootingTarget;
    void draw();
};

void SimpleShootingTargetInCircle::draw() {
  drawPlus(_x, _y, 5);
  _pencil->drawCircle(_x, _y, 4);
}

#endif
