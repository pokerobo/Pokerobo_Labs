#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  displayHandler.firstPage();
  do {
    drawPentagonOutline(5, 5, 115, 25, 100, 30, 85, 55, 40, 50);
  } while (displayHandler.nextPage());
}

void drawPentagonOutline(
      byte x1, byte y1,
      byte x2, byte y2,
      byte x3, byte y3,
      byte x4, byte y4,
      byte x5, byte y5
    ) {
  displayHandler.drawLine(x1, y1, x2, y2);
  displayHandler.drawLine(x2, y2, x3, y3);
  displayHandler.drawLine(x3, y3, x4, y4);
  displayHandler.drawLine(x4, y4, x5, y5);
  displayHandler.drawLine(x5, y5, x1, y1);
}
