#include "Balloon_Shooter-PlaySpace-Lib.h"

DemoPlaySpace::DemoPlaySpace(GeometryDisplayHandler* pencil,
    uint8_t concurrentTotal) {
  _pencil = pencil;
  _concurrentTotal = concurrentTotal;
}

void DemoPlaySpace::begin() {
  for(int k=0; k<_concurrentTotal; k++) {
    _balloons[k] = new DemoBalloon();
    _balloons[k]->set(_pencil);
  }
}

void DemoPlaySpace::change() {
  for(int i=0; i<_concurrentTotal; i++) {
    _balloons[i]->check();
  }
}

void DemoPlaySpace::draw() {
  for(int i=0; i<_concurrentTotal; i++) {
    drawFlyingBalloon(_balloons[i]);
  }
}

void DemoPlaySpace::drawFlyingBalloon(DemoBalloon* balloon) {
  balloon->draw();  
}
