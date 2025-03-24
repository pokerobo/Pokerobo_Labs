#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void plotPixel(int x, int y, GeometryDisplayHandler* displayHandler) {
  displayHandler->drawPixel(x, y);
}

void drawEllipse(int xm, int ym, int a, int b, GeometryDisplayHandler* displayHandler) {
  long x = -a, y = 0;           /* II. quadrant from bottom left to top right */
  long e2, dx = (1+2*x)*b*b;                              /* error increment  */
  long dy = x*x, err = dx+dy;                              /* error of 1.step */

  do {
    plotPixel(xm-x, ym+y, displayHandler);                   /*   I. Quadrant */
    plotPixel(xm+x, ym+y, displayHandler);                   /*  II. Quadrant */
    plotPixel(xm+x, ym-y, displayHandler);                   /* III. Quadrant */
    plotPixel(xm-x, ym-y, displayHandler);                   /*  IV. Quadrant */
    e2 = 2*err;                                        
    if (e2 >= dx) { x++; err += dx += 2*b*b; }                      /* x step */
    if (e2 <= dy) { y++; err += dy += 2*a*a; }                      /* y step */
  } while (x <= 0);

  while (y++ < b) {             /* too early stop for flat ellipses with a=1, */
    plotPixel(xm, ym+y, displayHandler);          /* -> finish tip of ellipse */
    plotPixel(xm, ym-y, displayHandler);
  }
}

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  displayHandler.firstPage();
  do {
    drawEllipse(60, 30, 35, 25, &displayHandler);
  } while (displayHandler.nextPage());
}
