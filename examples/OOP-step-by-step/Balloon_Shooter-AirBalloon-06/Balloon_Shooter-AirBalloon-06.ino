#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler dh;

class DemoBalloon {
  public:
    DemoBalloon(int cx, int cy, int cr) {
      _x = cx; _y = cy; _r = cr;
    }
    // method / phương thức / hành vi
    void check() {
      if (_y + _r >= 0) {
        _y = _y - 3;
      } else {
        _x = random(0, 128);
        _y = 63;
      }
    }
    void draw() {
      dh.drawCircle(_x, _y, _r);  
    }
    // Properties / thuộc tính
    int _x;
    int _y;
    int _r;
};

DemoBalloon b1(63, 63, 5); //int x = 63, y = 63; int r = 5;
DemoBalloon b2(80, 63, 8); //int x2 = 80, y2 = 63, r2 = 8;
DemoBalloon b3(20, 63, 13); // int x3 = 20, y3 = 63, r3 = 13;

void setup() {
  randomSeed(analogRead(A3));
  dh.begin();
}

void loop() {
  b1.check();
  b2.check();
  b3.check();

  dh.firstPage();
  do {
    b1.draw();
    b2.draw();
    b3.draw();
  } while(dh.nextPage());

  delay(50);
}
