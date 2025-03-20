#include "Pokerobo_Lab_Display_Handler.h"

class CornersDisplayHandlerWithPlus: public CornersDisplayHandler {
  protected:
    void drawCorner(uint16_t x, uint16_t y) {
      this->drawPixel(x, y);
      this->drawPixel(x+1, y);
      this->drawPixel(x, y+1);
      if (x > 0) {
        this->drawPixel(x-1, y);
      }
      if (y > 0) {
        this->drawPixel(x, y-1);
      }
    }
};

CornersDisplayHandlerWithPlus displayHandler;

void drawPageNumber(int i) {
  switch(i) {
    case 0:
      displayHandler.drawCorners(0, 0, 1, 1);
      break;
    case 1:
      displayHandler.drawCorners(0, 0, 0, 0);
      break;
    case 2:
      displayHandler.drawCorners(1, 1, 1, 1);
      break;
  }
}

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  for(int i=0; i<3; i++) {
    drawPageNumber(i);
    delay(5000);
  }
}
