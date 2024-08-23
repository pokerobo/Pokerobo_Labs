#include "IrRoboCarDispatcher.h"

IrRoboCarDispatcher::IrRoboCarDispatcher(RoboCarHandler *roboCarHandler) {
  if (roboCarHandler == NULL) exit(-1);
  _roboCarHandler = roboCarHandler;
}

uint8_t IrRoboCarDispatcher::getSpeed() {
  return _baseSpeed;
}

void IrRoboCarDispatcher::processOkButtonPressedEvent() {
  _roboCarHandler->stop();
}

void IrRoboCarDispatcher::processDPadUpButtonPressedEvent() {
  _roboCarHandler->move(1, getSpeed(), getSpeed(), 1);
}

void IrRoboCarDispatcher::processDPadRightButtonPressedEvent() {
  _roboCarHandler->move(1, getSpeed(), getSpeed(), 0);
}

void IrRoboCarDispatcher::processDPadDownButtonPressedEvent() {
  _roboCarHandler->move(-1, getSpeed(), getSpeed(), -1);
}

void IrRoboCarDispatcher::processDPadLeftButtonPressedEvent() {
  _roboCarHandler->move(0, getSpeed(), getSpeed(), 1);
}

void IrRoboCarDispatcher::processAsteriskButtonPressedEvent() {
  _roboCarHandler->turnOn();
}

void IrRoboCarDispatcher::processSharpButtonPressedEvent() {
  _roboCarHandler->turnOff();
}
