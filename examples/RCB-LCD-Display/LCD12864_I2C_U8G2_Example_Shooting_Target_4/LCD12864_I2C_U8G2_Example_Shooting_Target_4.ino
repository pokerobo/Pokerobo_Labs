#include <Pokerobo_RCB.h>
#include "Pokerobo_Lab_Aim_Target.h"

GeometryDisplayHandler displayHandler;

JoystickHandler joystickHandler;

class FasterShootingTarget: public ShootingTarget {
  public:
    using ShootingTarget::ShootingTarget;
    void toggleTurboMode();
    void draw();
  protected:
    int8_t getStepSpeedMax();
  private:
    bool _turboMode = true;
};

void FasterShootingTarget::toggleTurboMode() {
  _turboMode = !_turboMode;
}

void FasterShootingTarget::draw() {
  if (_turboMode) {
    int8_t x = getX();
    int8_t y = getY();
    drawCross(x, y, 5);
    getPencil()->drawCircle(x, y, 4);
  }
  ShootingTarget::draw();
}

int8_t FasterShootingTarget::getStepSpeedMax() {
  if (_turboMode) {
    return ShootingTarget::getStepSpeedMax()*3/2;
  }
  return ShootingTarget::getStepSpeedMax();
}

FasterShootingTarget target(&displayHandler);

void setup() {
  Serial.begin(57600);
  joystickHandler.begin();
  displayHandler.begin();
}

void loop() {
  JoystickAction action = joystickHandler.input();

  target.moveByJoystick(action.getX(), action.getY());
  if (action.isButtonClicked(MASK_SELECT_BUTTON)) {
    target.toggleTurboMode();
  }

  displayHandler.firstPage();
  do {
    target.draw();
  } while (displayHandler.nextPage());

  delay(10);
}
