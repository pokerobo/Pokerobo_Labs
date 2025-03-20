#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  displayHandler.firstPage();
  do {
    displayHandler.drawLine(10, 10, 50, 50); // line #1
    displayHandler.drawLine(10, 50, 100, 4); // line #2
    displayHandler.drawLine(5, 32, 120, 32); // line #3
    displayHandler.drawLine(64, 10, 64, 50); // line #4
  } while (displayHandler.nextPage());
}
