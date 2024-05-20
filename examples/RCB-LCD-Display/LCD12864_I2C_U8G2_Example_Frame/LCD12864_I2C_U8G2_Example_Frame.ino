#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

void loop() {
  displayHandler.firstPage();
  do {
    // Khung hình chữ nhật
    // bắt đầu tại tọa độ (10, 10), dài 108 pixel, cao 44 pixel
    displayHandler.drawFrame(10, 10, 108, 44);

    // Đánh dấu điểm bắt đầu của khung hình chữ nhật bên trên
    displayHandler.drawFrame(9, 9, 3, 3);
  } while (displayHandler.nextPage());
}
