#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void drawAsterisk(int x, int y, int radius) {
  displayHandler.drawLine(x, y - radius, x, y + radius);
    displayHandler.drawLine(x - radius, y, x + radius, y);

    int len2 = radius / sqrt(2);
    displayHandler.drawLine(x - len2, y - len2, x + len2, y + len2);
    displayHandler.drawLine(x - len2, y + len2, x + len2, y - len2);
}

void loop() {
  int len = 10;
  int x = 100;
  int y = 40;

  displayHandler.firstPage();
  do {
    drawAsterisk(x, y, len);
  } while (displayHandler.nextPage());
}
