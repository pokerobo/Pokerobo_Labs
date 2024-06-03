#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  displayHandler.firstPage();
  do {
    displayHandler.drawLine(63, (31 - 10), 63, (31 + 10));
    displayHandler.drawLine((63 - 10), 31, (63 + 10), 31);

    displayHandler.drawLine((63 - 10), (31 - 10), (63 + 10), (31 + 10));
    displayHandler.drawLine((63 - 10), (31 + 10), (63 + 10), (31 - 10));
 
  } while (displayHandler.nextPage());
}
