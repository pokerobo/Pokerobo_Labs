#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
  displayHandler.firstPage();
  do {
    uint16_t charWidth = displayHandler.getMaxCharWidth();
    uint16_t charHeight = displayHandler.getMaxCharHeight();
    uint16_t displayWidth = displayHandler.getDisplayWidth();
    uint16_t displayHeight = displayHandler.getDisplayHeight();
    char text[16] = { 0 };
    sprintf(text, "%dx%d", displayWidth, displayHeight);
    displayHandler.drawStr((displayWidth - strlen(text)*charWidth)/2, displayHeight/2, text);
  } while (displayHandler.nextPage());
}

void loop() {
}
