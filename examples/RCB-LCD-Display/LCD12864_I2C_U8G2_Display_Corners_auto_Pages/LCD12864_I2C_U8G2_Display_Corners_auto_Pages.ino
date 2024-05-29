#include "Pokerobo_Lab_Display_Handler.h"

CornersDisplayHandler displayHandler;

void drawPageNumber(int i) {
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
