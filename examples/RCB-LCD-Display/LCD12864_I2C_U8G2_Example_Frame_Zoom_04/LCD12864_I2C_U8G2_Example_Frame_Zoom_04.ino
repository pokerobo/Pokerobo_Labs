#include "Pokerobo_Lab_Display_Handler.h"

const int delayTotal = 100;

GeometryDisplayHandler displayHandler;

// O(x, y), width, height
int x = 10, y = 10, w = 108, h = 44;
int dx = 4, dy = 2;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  for(int i=0; w - i*dx*2 > 0 && h - i*dy*2 > 0; i++) {
    displayHandler.firstPage();
    do {
      displayHandler.drawFrame(x + i*dx, y + i*dy, w - i*dx*2, h - i*dy*2);
    } while (displayHandler.nextPage());
    delay(delayTotal);
  }
}
