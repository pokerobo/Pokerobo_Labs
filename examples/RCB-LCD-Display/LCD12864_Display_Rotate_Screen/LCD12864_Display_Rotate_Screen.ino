#include "Pokerobo_Lab_Display_Handler.h"

JoystickHandler joystickHandler;
JoystickAction joystickAction;

GeometryDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  joystickHandler.begin();
  displayHandler.begin();
}

void loop() {
  joystickHandler.input(&joystickAction);
  uint16_t flags = joystickAction.getTogglingFlags();
  if ((flags & MASK_LEFT_BUTTON) == MASK_LEFT_BUTTON) {
    displayHandler.rotateScreen(false);
  }
  if ((flags & MASK_RIGHT_BUTTON) == MASK_RIGHT_BUTTON) {
    displayHandler.rotateScreen(true);
  }

  displayHandler.firstPage();
  do {
    displayHandler.showDisplayInfo();
  } while (displayHandler.nextPage());

  delay(100);
}
