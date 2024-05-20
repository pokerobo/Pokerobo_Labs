#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();

  byte x1=5, y1=5, x2=115, y2=25, x3=120, y3=45, x4=85, y4=64, x5=40, y5=50;

  displayHandler.firstPage();
  do {
    drawPentagonOutline(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5);
  } while (displayHandler.nextPage());
  delay(3000);

  displayHandler.firstPage();
  do {
    drawPentagonOutline(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5);
    drawScanningLines(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5);
  } while (displayHandler.nextPage());
  delay(3000);

  displayHandler.firstPage();
  do {
    drawPentagonConvexShape(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5);
  } while (displayHandler.nextPage());
  delay(4000);
}

void loop() {
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

void drawScanningLines(
      byte x1, byte y1,
      byte x2, byte y2,
      byte x3, byte y3,
      byte x4, byte y4,
      byte x5, byte y5
    ) {
  displayHandler.drawLine(x1, y1, x3, y3);
  displayHandler.drawLine(x1, y1, x4, y4);
}

void drawPentagonConvexShape(
      byte x1, byte y1,
      byte x2, byte y2,
      byte x3, byte y3,
      byte x4, byte y4,
      byte x5, byte y5
    ) {
  displayHandler.drawTriangle(x1, y1, x2, y2, x3, y3);
  displayHandler.drawTriangle(x1, y1, x3, y3, x4, y4);
  displayHandler.drawTriangle(x1, y1, x4, y4, x5, y5);
}
