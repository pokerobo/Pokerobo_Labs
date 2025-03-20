#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  displayHandler.firstPage();
  do {
    displayHandler.setFont(text_font_title_bold);
    displayHandler.drawStr(20, 32, "Hello world!");
  } while (displayHandler.nextPage());
}
