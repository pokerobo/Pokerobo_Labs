#include "Pokerobo_Lab_Display_Handler.h"

JoystickHandler joystickHandler;
JoystickAction joystickAction;

CornersDisplayHandler displayHandler;

const int total = 3;

void drawPageNumber(int i) {
  switch(i) {
    case 0:
      displayHandler.drawPage(total, i, 0, 0, 1, 1);
      break;
    case 1:
      displayHandler.drawPage(total, i, 0, 0, 0, 0);
      break;
    case 2:
      displayHandler.drawPage(total, i, 1, 1, 1, 1);
      break;
  }
}

int count = 0;

int nextPage() {
  count += 1;
  if (count >= total) {
    count = 0;
  }
  return count;
}

int prevPage() {
  count--;
  if (count < 0) {
    count = total - 1;
  }
  return count;
}

void setup() {
  Serial.begin(57600);
  joystickHandler.begin();
  displayHandler.begin();
}

void loop() {
  joystickHandler.input(&joystickAction);
  uint16_t flags = joystickAction.getTogglingFlags();
  if ((flags & MASK_LEFT_BUTTON) == MASK_LEFT_BUTTON) {
    drawPageNumber(prevPage());
  }
  if ((flags & MASK_RIGHT_BUTTON) == MASK_RIGHT_BUTTON) {
    drawPageNumber(nextPage());
  }
  delay(10);
}
