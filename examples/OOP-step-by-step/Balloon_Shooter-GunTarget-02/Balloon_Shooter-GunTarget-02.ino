// Khai báo thư viện
#include "Pokerobo_Lab_Display_Handler.h"

JoystickAction action;
JoystickHandler joystickHandler;
GeometryDisplayHandler displayHandler;

int x = 20;
int y = 20;
int r = 3;

int speedOfX(int jX) {
  int nX = -512 + jX; // jX - 512
  if (abs(nX) < 30) nX = 0;
  return map(nX, -512, 512, -10, 10);
}

int speedOfY(int jY) {
  int nY = -512 + jY; // jY - 512
  if (abs(nY) < 30) nY = 0;
  return map(nY, -512, 512, 10, -10);
}

void move(int dX, int dY) {
  x = x + dX > 0 ? (x + dX <= 127 ? x + dX : 127) : 0;
  y = (y + dY > 0) ? (y + dY <= 63 ? y + dY : 63) : 0;
}

void draw() {
  displayHandler.drawPixel(x, y);
  displayHandler.drawCircle(x, y, r);
}

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
  joystickHandler.begin();
}

void loop() {
  joystickHandler.input(&action);

  move(speedOfX(action.getX()), speedOfY(action.getY()));

  displayHandler.firstPage();
  do {
    draw();
  } while(displayHandler.nextPage());

  delay(50);
}
