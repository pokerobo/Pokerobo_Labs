#include "Pokerobo_Lab_Display_Handler.h"

const int delayTotal = 100;

GeometryDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  int x = 10, y = 10, w = 108, h = 44;
  for(int i=0; w > i*10*2 && h > i*5*2; i++) {
    displayHandler.firstPage();
    do {
      displayHandler.drawFrame(x + i*10, y + i*5, w - i*10*2, h - i*5*2);
    } while (displayHandler.nextPage());
    delay(delayTotal);
  }
}
