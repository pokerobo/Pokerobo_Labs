#include "Pokerobo_Lab_Display_Handler.h"

class CornersDisplayHandler: public GeometryDisplayHandler {
  public:
    void drawPage(uint8_t total, uint8_t number, uint16_t h0, uint16_t v0, uint16_t h1, uint16_t v1);
    void drawCorners(const char* label, uint16_t h0, uint16_t v0, uint16_t h1, uint16_t v1);
  protected:
    virtual void drawCorner(uint16_t x, uint16_t y);
};

void CornersDisplayHandler::drawCorner(uint16_t x, uint16_t y) {
  this->drawPixel(x, y);
  this->drawPixel(x+1, y+1);
  if (y > 0) {
    this->drawPixel(x+1, y-1);
  }
  if (x > 0) {
    this->drawPixel(x-1, y+1);
  }
  if (x > 0 & y > 0) {
    this->drawPixel(x-1, y-1);
  }
}

void CornersDisplayHandler::drawPage(uint8_t total, uint8_t number, uint16_t h0, uint16_t v0, uint16_t h1, uint16_t v1) {
  char label[total + 1] = { 0 };
  for(int i=0; i<total; i++) {
    if (i == number) {
      label[i] = '0' + i;
    } else {
      label[i] = '-';
    }
  }
  drawCorners(label, h0, v0, h1, v1);
}

void CornersDisplayHandler::drawCorners(const char* label, uint16_t h0, uint16_t v0, uint16_t h1, uint16_t v1) {
  uint16_t charWidth = this->getMaxCharWidth();
  uint16_t charHeight = this->getMaxCharHeight();
  uint16_t displayWidth = this->getDisplayWidth();
  uint16_t displayHeight = this->getDisplayHeight();

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

  this->firstPage();
  do {
    if (label != NULL) {
      this->drawStr(displayWidth/2 - charWidth*strlen(label)/2,
        charHeight + 1, label);
    }

    drawCorner(x0, y0);
    drawCorner(x1, y1);
    drawCorner(x2, y2);
    drawCorner(x3, y3);

    for(int i=0; i<4; i++) {
      this->drawStr(displayWidth/2 - charWidth*strlen(lines[i])/2,
          textBlockY + i*(charHeight + 1), lines[i]);
    }
  } while (this->nextPage());
}

CornersDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  for(int i=0; i<3; i++) {
    switch(i) {
      case 0:
        displayHandler.drawPage(3, i, 0, 0, 1, 1);
        break;
      case 1:
        displayHandler.drawPage(3, i, 0, 0, 0, 0);
        break;
      case 2:
        displayHandler.drawPage(3, i, 1, 1, 1, 1);
        break;
    }
    delay(5000);
  }
}
