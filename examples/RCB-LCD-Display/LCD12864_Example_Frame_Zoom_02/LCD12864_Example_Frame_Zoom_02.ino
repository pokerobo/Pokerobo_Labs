#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;
const int delayTotal = 100;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  for(int i=0; i<4; i++) { // i++ ~ i = i + 1
    displayHandler.firstPage();
    do {
      displayHandler.drawFrame(10 + i*10, 10 + i*5, 108 - i*10*2, 44 - i*5*2);
    } while (displayHandler.nextPage());
    delay(delayTotal);
  }
}
