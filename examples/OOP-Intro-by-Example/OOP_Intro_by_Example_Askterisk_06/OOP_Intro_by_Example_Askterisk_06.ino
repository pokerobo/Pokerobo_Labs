#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

JoystickHandler joystickHandler;
JoystickAction joystickControl;

void setup() {
  Serial.begin(57600);
  joystickHandler.begin();
  displayHandler.begin();
}

int gt0(int v) {
  return (v > 0) ? v : 0;
}

void drawAsterisk(int x, int y, int radius = 20) {
  displayHandler.drawLine(x, gt0(y - radius), x, y + radius);
  displayHandler.drawLine(gt0(x - radius), y, x + radius, y);

  int len2 = radius / sqrt(2);
  int cutx = min(len2, x);
  int cuty = min(len2, y);
  int cutz = min(cutx, cuty);

  displayHandler.drawLine(x - cutz, y - cutz, x + len2, y + len2);
  displayHandler.drawLine(x - cutx, y + cutx, x + cuty, y - cuty);
}

void loop() {
  joystickHandler.input(&joystickControl);

  int x = map(joystickControl.getX(), 0, 1023, 0, 127);
  int y = map(joystickControl.getY(), 0, 1023, 63,  0);

  displayHandler.firstPage();
  do {
    drawAsterisk(x, y); // uses default radius ~ 20
  } while (displayHandler.nextPage());
}
