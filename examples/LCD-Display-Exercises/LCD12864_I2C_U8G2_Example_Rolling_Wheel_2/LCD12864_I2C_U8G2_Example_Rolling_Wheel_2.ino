#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler dh;

class Wheel {
  int r = 15;
  int x = 0;
  int y = 0;
  public:
    Wheel() {
      x = r;
      y = 63 - r;
    };
    void swing(int speed, byte &direction) {
      if (direction) {
        x = x + speed;
        if (x > 127 - r) {
          x = 127 - r;
        }
        if (x == 127 - r) {
          direction = 1 - direction;
        }
      } else {
        x = x - speed;
        if (x < r) {
          x = r;
        }
        if (x == r) {
          direction = 1 - direction;
        }
      }
    };
    void draw() {
      dh.drawCircle(x, y, r);
    };
};

int speed = 3;
byte direction = 1;
Wheel w;

void setup() {
  dh.begin();
}

void loop() {
  w.swing(speed, direction);
  dh.firstPage();
  do {
    w.draw();
  } while(dh.nextPage());
  delay(50);
}
