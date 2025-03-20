#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  displayHandler.firstPage();
  do {
    // Hình chữ nhật (đặc)
    // bắt đầu tại tọa độ (10, 10), dài 108 pixel, cao 44 pixel
    displayHandler.drawBox(10, 10, 108, 44);
  } while (displayHandler.nextPage());
}
