#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler dh;

class DemoBalloon {
  public:
    DemoBalloon(int cx, int cy, int cr) {
      _x = cx; _y = cy; _r = cr;
    }

    void check() {
      if (_y + _r >= 0) {
        _y = _y - 3;
      } else {
        _y = 63 + _r;
        _x = random(0, 128);
      }
    }
    void draw() {
      dh.drawCircle(_x, _y, _r);
    }

    int _x;
    int _y;
    int _r;
};

DemoBalloon b1(63, 63, 5);
DemoBalloon b2(80, 63, 8);
DemoBalloon b3(20, 63, 6);

const int numOfBalls = 4;

DemoBalloon balls[numOfBalls] = {
  DemoBalloon(40, 63, 9),
  b1, b2, b3
};

void setup() {
  randomSeed(analogRead(A3));
  dh.begin();
}

void loop() {
  for(int i=0; i<numOfBalls; i++) {
    balls[i].check();
  }

  dh.firstPage();
  do {
    for(int i=0; i<numOfBalls; i++) {
      balls[i].draw();
    }
  } while(dh.nextPage());

  delay(50);
}
