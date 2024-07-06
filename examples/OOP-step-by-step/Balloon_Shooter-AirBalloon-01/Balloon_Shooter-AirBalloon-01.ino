#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler dh;

int x = 63, y = 63; int r = 5;

void setup() {
  dh.begin();
}

void loop() {
  // y là tọa độ tâm đường tròn, y + r là điểm thấp nhất của quả bóng
  // điểm thấp nhất của quả bóng mà vượt qua khỏi đường biên
  // bên trên màn hình, thì không cần phải bay lên nữa
  if (y + r >= 0) {
    y = y - 3;
  } else {
    y = 63;
  }

  dh.firstPage();
  do {
    dh.drawCircle(x, y, r);
  } while(dh.nextPage());

  delay(50);
}
