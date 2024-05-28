#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void drawCross(uint16_t x, uint16_t y) {
  displayHandler.drawPixel(x, y);
  displayHandler.drawPixel(x+1, y+1);
  if (y > 0) {
    displayHandler.drawPixel(x+1, y-1);
  }
  if (x > 0) {
    displayHandler.drawPixel(x-1, y+1);
  }
  if (x > 0 & y > 0) {
    displayHandler.drawPixel(x-1, y-1);
  }
}

void drawCorners(uint8_t total, uint8_t number, uint16_t h0, uint16_t v0, uint16_t h1, uint16_t v1) {
  char label[total + 1] = { 0 };
  for(int i=0; i<total; i++) {
    if (i == number) {
      label[i] = '0' + i;
    } else {
      label[i] = '-';
    }
  }

  uint16_t charWidth = displayHandler.getMaxCharWidth();
  uint16_t charHeight = displayHandler.getMaxCharHeight();
  uint16_t displayWidth = displayHandler.getDisplayWidth();
  uint16_t displayHeight = displayHandler.getDisplayHeight();

  uint16_t x0 = h0, y0 = v0;
  uint16_t x1 = displayWidth - h1, y1 = v0;
  uint16_t x2 = displayWidth - h1, y2 = displayHeight - v1;
  uint16_t x3 = h0, y3 = displayHeight - v1;

  char lines[4][16] = { {0}, {0}, {0}, {0} };
  sprintf(lines[0], "C%d: %3d,%2d", 0, x0, y0);
  sprintf(lines[1], "C%d: %3d,%2d", 1, x1, y1);
  sprintf(lines[2], "C%d: %3d,%2d", 2, x2, y2);
  sprintf(lines[3], "C%d: %3d,%2d", 3, x3, y3);

  uint16_t textBlockX = displayWidth/2 - 3*charWidth;
  uint16_t textBlockY = displayHeight/2 - 1*(charHeight + 1);

  displayHandler.firstPage();
  do {
    displayHandler.drawStr(displayWidth/2 - charWidth*strlen(label)/2,
      charHeight + 1, label);

    drawCross(x0, y0);
    drawCross(x1, y1);
    drawCross(x2, y2);
    drawCross(x3, y3);

    for(int i=0; i<4; i++) {
      displayHandler.drawStr(displayWidth/2 - charWidth*strlen(lines[i])/2,
          textBlockY + i*(charHeight + 1), lines[i]);
    }
  } while (displayHandler.nextPage());
}

void loop() {
  for(int i=0; i<3; i++) {
    switch(i) {
      case 0:
        drawCorners(3, i, 0, 0, 1, 1);
        break;
      case 1:
        drawCorners(3, i, 0, 0, 0, 0);
        break;
      case 2:
        drawCorners(3, i, 1, 1, 1, 1);
        break;
    }
    delay(5000);
  }
}
