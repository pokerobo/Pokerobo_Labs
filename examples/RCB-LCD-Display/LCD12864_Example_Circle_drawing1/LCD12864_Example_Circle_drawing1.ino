#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void drawCircle(int x, int y, int r, GeometryDisplayHandler* displayHandler) {
  float i, angle, x1, y1;

  for(i = 0; i < 360; i += 1.5) {
    angle = i;
    x1 = r * cos(angle * PI / 180);
    y1 = r * sin(angle * PI / 180);
    displayHandler->drawPixel(x + x1, y + y1);
  }
}

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  displayHandler.firstPage();
  do {
    drawCircle(40, 31, 30, &displayHandler);
  } while (displayHandler.nextPage());
}
