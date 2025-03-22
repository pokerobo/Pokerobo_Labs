#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void plotPixel(int x, int y, GeometryDisplayHandler* displayHandler) {
  displayHandler->drawPixel(x, y);
}

void drawCircle(int xc, int yc, int r, GeometryDisplayHandler* displayHandler) {
  int x = -r, y = 0, err = 2-2*r;
  do {
    plotPixel(xc-x, yc+y, displayHandler);
    plotPixel(xc-y, yc-x, displayHandler);
    plotPixel(xc+x, yc-y, displayHandler);
    plotPixel(xc+y, yc+x, displayHandler);
    r = err;
    if (r <= y) {
      err += ++y*2+1;
    }
    if (r > x || err > y) {
      err += ++x*2+1;
    }
  } while (x < 0);
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
