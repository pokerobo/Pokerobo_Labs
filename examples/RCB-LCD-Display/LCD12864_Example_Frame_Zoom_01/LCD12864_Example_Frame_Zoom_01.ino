#include "Pokerobo_Lab_Display_Handler.h"

const int delayTotal = 100;

GeometryDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  displayHandler.firstPage();
  do {
    displayHandler.drawFrame(10, 10, 108, 44);
    // displayHandler.drawFrame(10 + 0*10, 10 + 0*5, 108 - 0*10*2, 44 - 0*5*2);
    // displayHandler.drawFrame(10 + i*10, 10 + i*5, 108 - i*10*2, 44 - i*5*2); // i=0
  } while (displayHandler.nextPage());
  delay(delayTotal);
  
  displayHandler.firstPage();
  do {
    displayHandler.drawFrame(10 + 10, 10 + 5, 108 - 10*2, 44 - 5*2);
    // displayHandler.drawFrame(10 + 1*10, 10 + 1*5, 108 - 1*10*2, 44 - 1*5*2);
    // displayHandler.drawFrame(10 + i*10, 10 + i*5, 108 - i*10*2, 44 - i*5*2); // i=1
  } while (displayHandler.nextPage());
  delay(delayTotal);

  displayHandler.firstPage();
  do {
    displayHandler.drawFrame(10 + 2*10, 10 + 2*5, 108 - 2*10*2, 44 - 2*5*2);
    // displayHandler.drawFrame(10 + i*10, 10 + i*5, 108 - i*10*2, 44 - i*5*2); // i=2
  } while (displayHandler.nextPage());
  delay(delayTotal);

  displayHandler.firstPage();
  do {
    displayHandler.drawFrame(10 + 3*10, 10 + 3*5, 108 - 3*10*2, 44 - 3*5*2);
    // displayHandler.drawFrame(10 + i*10, 10 + i*5, 108 - i*10*2, 44 - i*5*2); // i=3
  } while (displayHandler.nextPage());
  delay(delayTotal);
}
