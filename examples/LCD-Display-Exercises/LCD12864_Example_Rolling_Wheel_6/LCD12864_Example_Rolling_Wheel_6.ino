#include "Pokerobo_Lab_Rolling_Wheel.h"

GeometryDisplayHandler dh;
JoystickHandler joystickHandler;
JoystickAction joystickAction;

bool autorun = false;
byte direction = 1;
int speed = 3;
Wheel w(&dh);

void setup() {
  Serial.begin(57600);
  dh.begin();
  joystickHandler.begin();
  w.begin();
}

void loop() {
  joystickHandler.input(&joystickAction);

  if (joystickAction.isButtonClicked(MASK_ANALOG_BUTTON)) {
    autorun = !autorun;
  }

  if (autorun) {
    w.swing(speed, direction);
  } else {
    if (joystickAction.isButtonPressed(MASK_LEFT_BUTTON)) {
      w.roll(speed, 0);
    }
    if (joystickAction.isButtonPressed(MASK_RIGHT_BUTTON)) {
      w.roll(speed, 1);
    }
  }

  dh.firstPage();
  do {
    w.draw();
  } while(dh.nextPage());
  delay(50);
}
