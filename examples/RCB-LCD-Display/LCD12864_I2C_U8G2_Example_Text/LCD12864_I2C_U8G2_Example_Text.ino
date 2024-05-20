#include <U8g2lib.h>
#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  displayHandler.firstPage();
  do {
    displayHandler.setFont(u8g2_font_ncenB10_tr);
    displayHandler.drawStr(20, 32, "Hello world!");
  } while (displayHandler.nextPage());
}
