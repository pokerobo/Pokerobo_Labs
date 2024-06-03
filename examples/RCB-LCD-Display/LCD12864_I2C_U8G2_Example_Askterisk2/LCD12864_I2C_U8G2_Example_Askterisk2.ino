#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  int len = 10;

  displayHandler.firstPage();
  do {
    displayHandler.drawLine(63, (31 - len), 63, (31 + len));
    displayHandler.drawLine((63 - len), 31, (63 + len), 31);

    displayHandler.drawLine((63 - len), (31 - len), (63 + len), (31 + len));
    displayHandler.drawLine((63 - len), (31 + len), (63 + len), (31 - len));

  } while (displayHandler.ne63tPage());
}
