#include "Pokerobo_Lab_Display_Handler.h"

class ExtendDisplayHandler: public GeometryDisplayHandler {
  public:
    using GeometryDisplayHandler::GeometryDisplayHandler;
    void drawLine(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t x1, u8g2_uint_t y1);
};

void drawLine_(int x0, int y0, int x1, int y1, ExtendDisplayHandler* displayHandler) {
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;

  for(;;){
    displayHandler->drawPixel(x0, y0);
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

void ExtendDisplayHandler::drawLine(u8g2_uint_t x0, u8g2_uint_t y0,
    u8g2_uint_t x1, u8g2_uint_t y1) {
  drawLine_(x0, y0, x1, y1, this);
}

ExtendDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  displayHandler.firstPage();
  do {
    displayHandler.drawLine(10, 10, 50, 50); // line #1
    displayHandler.drawLine(10, 50, 100, 4); // line #2
    displayHandler.drawLine(5, 32, 120, 32); // line #3
    displayHandler.drawLine(64, 10, 64, 50); // line #4
  } while (displayHandler.nextPage());
}
