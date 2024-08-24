#include "IrRoboCarDispatcher.h"

#define IR_MASK_DIGIT1_BUTTON   1UL << (7+1)
#define IR_MASK_DIGIT2_BUTTON   1UL << (7+2)
#define IR_MASK_DIGIT3_BUTTON   1UL << (7+3)

IrRoboCarDispatcher::IrRoboCarDispatcher(RoboCarHandler *roboCarHandler) {
  // if (roboCarHandler == NULL) exit(-1);
  _roboCarHandler = roboCarHandler;
}

int IrRoboCarDispatcher::getSpeed() {
  return _baseSpeed + _gearNumber * 10;
}

void IrRoboCarDispatcher::processOkButtonPressedEvent() {
  _roboCarHandler->stop();
}

void IrRoboCarDispatcher::processDPadUpButtonPressedEvent() {
  if (_sharpButtonState) {
    _reversed = false;
    _sharpButtonState = !_sharpButtonState;
    return;
  }
  _roboCarHandler->move(1, getSpeed(), getSpeed(), 1, _reversed);
}

void IrRoboCarDispatcher::processDPadRightButtonPressedEvent() {
  _roboCarHandler->move(1, getSpeed(), getSpeed(), 0, _reversed);
}

void IrRoboCarDispatcher::processDPadDownButtonPressedEvent() {
  if (_sharpButtonState) {
    _reversed = true;
    _sharpButtonState = !_sharpButtonState;
    return;
  }
  _roboCarHandler->move(-1, getSpeed(), getSpeed(), -1, _reversed);
}

void IrRoboCarDispatcher::processDPadLeftButtonPressedEvent() {
  _roboCarHandler->move(0, getSpeed(), getSpeed(), 1, _reversed);
}

void IrRoboCarDispatcher::processAsteriskButtonPressedEvent() {
  _asteriskButtonState = !_asteriskButtonState;
  if (_asteriskButtonState) {
    _roboCarHandler->turnOn();
  } else {
    _roboCarHandler->turnOff();
  }
}

void IrRoboCarDispatcher::processSharpButtonPressedEvent() {
  _sharpButtonState = !_sharpButtonState;
}

void IrRoboCarDispatcher::processDigitButtonsPressedEvent(uint32_t buttons) {
  if (buttons & IR_MASK_DIGIT1_BUTTON) {
    _gearNumber = 1;
    return;
  }
  if (buttons & IR_MASK_DIGIT2_BUTTON) {
    _gearNumber = 2;
    return;
  }
  if (buttons & IR_MASK_DIGIT3_BUTTON) {
    _gearNumber = 3;
    return;
  }
}
