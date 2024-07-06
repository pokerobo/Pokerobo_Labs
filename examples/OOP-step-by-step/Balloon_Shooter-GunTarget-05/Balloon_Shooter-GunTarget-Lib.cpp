#include "Balloon_Shooter-GunTarget-Lib.h"

DemoGunTarget::DemoGunTarget(GeometryDisplayHandler* displayHandler) {
  _pencil = displayHandler;
}

int DemoGunTarget::getX() { return x; }
int DemoGunTarget::getY() { return y; }

int DemoGunTarget::speedOfX(int jX) {
  int dX = -512 + jX; // jX - 512
  if (abs(dX) < 30) dX = 0;
  return map(dX, -512, 512, -10, 10);
}

int DemoGunTarget::speedOfY(int jY) {
  int dY = -512 + jY; // jY - 512
  if (abs(dY) < 30) dY = 0;
  return map(dY, -512, 512, 10, -10);
}

void DemoGunTarget::move(int dX, int dY) {
  int _maxX = _pencil->getMaxX();
  int _maxY = _pencil->getMaxY();
  x = x + dX > 0 ? (x + dX <= _maxX ? x + dX : _maxX) : 0;
  y = y + dY > 0 ? (y + dY <= _maxY ? y + dY : _maxY) : 0;
}

void DemoGunTarget::update(int jX, int jY) {
  move(speedOfX(jX), speedOfY(jY));
}

void DemoGunTarget::draw() {
  _pencil->drawPixel(x, y);
  _pencil->drawCircle(x, y, r);
}
