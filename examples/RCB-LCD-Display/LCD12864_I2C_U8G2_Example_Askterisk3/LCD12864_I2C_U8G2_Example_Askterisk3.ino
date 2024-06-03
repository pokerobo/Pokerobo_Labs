#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  int len = 10;
  int x = 100;
  int y = 40;

  displayHandler.firstPage();
  do {
    displayHandler.drawLine(x, (y - len), x, (y + len));
    displayHandler.drawLine((x - len), y, (x + len), y);

    displayHandler.drawLine((x - len), (y - len), (x + len), (y + len));
    displayHandler.drawLine((x - len), (y + len), (x + len), (y - len));
 
  } while (displayHandler.nextPage());
}
