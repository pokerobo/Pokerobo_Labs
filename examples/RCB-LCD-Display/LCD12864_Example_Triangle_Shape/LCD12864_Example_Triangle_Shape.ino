#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  displayHandler.firstPage();
  do {
    displayHandler.drawTriangle(5, 5, 115, 25, 85, 55);
  } while (displayHandler.nextPage());
}
