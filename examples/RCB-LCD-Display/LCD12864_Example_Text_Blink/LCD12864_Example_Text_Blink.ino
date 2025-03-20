#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  writeText(20, 32, "Hello world!");
  delay(2000);
  clearScreen();
  delay(1000);
}

void writeText(byte x, byte y, char* text) {
  displayHandler.firstPage();
  do {
    displayHandler.setFont(text_font_title_bold);
    displayHandler.drawStr(x, y, text);
  } while (displayHandler.nextPage());
}

void clearScreen() {
  displayHandler.clear();
}
