#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void setup() {
  displayHandler.begin();
}

byte cx=64; //x center
byte cy=45; //y center
byte radius=40; //radius
byte radius2=30; //radius

void drawGauge(int x, byte y, byte r, byte r2, int v, int minVal, int maxVal) {
  displayHandler.firstPage();
  do {
    displayHandler.drawCircle(x, y, r, U8G2_DRAW_UPPER_LEFT|U8G2_DRAW_UPPER_RIGHT);
    displayHandler.drawCircle(x, y, r2, U8G2_DRAW_UPPER_LEFT|U8G2_DRAW_UPPER_RIGHT);
    displayHandler.drawLine(cx-r, cy, cx-r2, cy);
    displayHandler.drawLine(cx+r, cy, cx+r2, cy);
    displayHandler.setDrawColor(1);
    displayHandler.drawStr(x-30, y+15, "Value:");
    displayHandler.drawStr(x+7, y+15, v);
    float val = map(v, minVal, maxVal, 0, 180);
    val = val*3.14/180 -1.572;
    int xp = x+(sin(val) * r);
    int yp = y-(cos(val) * r);
    displayHandler.drawLine(x, y, xp, yp);
    displayHandler.drawLine(x-1, y-1, xp, yp);
    displayHandler.drawLine(x+1, y-1, xp, yp);
    displayHandler.drawLine(x-1, y, xp, yp);
    displayHandler.drawLine(x+1, y, xp, yp);
  } while (displayHandler.nextPage());
}

void loop() {
  drawGauge(cx, cy, radius, radius2, random(100), 0, 100);
  delay(500);
}
