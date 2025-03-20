#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void drawCircle_(int xc, int yc, int x, int y, GeometryDisplayHandler* displayHandler) {
    displayHandler->drawPixel(xc+x, yc+y);
    displayHandler->drawPixel(xc-x, yc+y);
    displayHandler->drawPixel(xc+x, yc-y);
    displayHandler->drawPixel(xc-x, yc-y);
    displayHandler->drawPixel(xc+y, yc+x);
    displayHandler->drawPixel(xc-y, yc+x);
    displayHandler->drawPixel(xc+y, yc-x);
    displayHandler->drawPixel(xc-y, yc-x);
}

void drawCircle(int xc, int yc, int r, GeometryDisplayHandler* displayHandler) {
  int x = 0, y = r;
  int d = 3 - 2 * r;
  drawCircle_(xc, yc, x, y, displayHandler);
  while (y >= x){
    // check for decision parameter and correspondingly update d, y
    if (d > 0) {
      y--;
      d = d + 4 * (x - y) + 10;
    } else {
      d = d + 4 * x + 6;
    }
    // increment x after updating decision parameter
    x++;
    // draw the circle using the new coordinates
    drawCircle_(xc, yc, x, y, displayHandler);
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
