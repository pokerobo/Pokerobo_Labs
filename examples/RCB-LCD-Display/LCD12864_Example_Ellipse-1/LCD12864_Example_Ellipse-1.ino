#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void setPixel(int x, int y, GeometryDisplayHandler* displayHandler) {
  displayHandler->drawPixel(x, y);
}

void plotEllipseRect(int x0, int y0, int x1, int y1, GeometryDisplayHandler* displayHandler) {
  long a = abs(x1-x0), b = abs(y1-y0), b1 = b&1;
  long dx = 4*(1-a)*b*b, dy = 4*(b1+1)*a*a;
  long err = dx+dy+b1*a*a, e2;

  if (x0 > x1) { x0 = x1; x1 += a; }
  if (y0 > y1) y0 = y1;
  y0 += (b+1)/2; y1 = y0-b1;
  a *= 8*a; b1 = 8*b*b;

  do {
    setPixel(x1, y0, displayHandler);
    setPixel(x0, y0, displayHandler);
    setPixel(x0, y1, displayHandler);
    setPixel(x1, y1, displayHandler);
    e2 = 2*err;
    if (e2 <= dy) { y0++; y1--; err += dy += a; }
    if (e2 >= dx || 2*err > dy) { x0++; x1--; err += dx += b1; }
  } while (x0 <= x1);
   
  while (y0-y1 < b) {
    setPixel(x0-1, y0, displayHandler);
    setPixel(x1+1, y0++, displayHandler);
    setPixel(x0-1, y1, displayHandler);
    setPixel(x1+1, y1--, displayHandler);
  }
}

void drawEllipse(int xc, int yc, int a, int b, GeometryDisplayHandler* displayHandler) {
  plotEllipseRect(xc - a, yc - b, xc + a, yc + b, displayHandler);
}

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  displayHandler.firstPage();
  do {
    drawEllipse(60, 30, 40, 20, &displayHandler);
  } while (displayHandler.nextPage());
}
