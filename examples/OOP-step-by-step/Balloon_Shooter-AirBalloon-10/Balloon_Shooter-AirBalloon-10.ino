#include "Pokerobo_Lab_Display_Handler.h"

bool exec() {
  randomSeed(analogRead(A3));
  return true;
}
bool _ = exec();

GeometryDisplayHandler dh;

class DemoBalloon {
  public:
    // Constructors
    DemoBalloon() { init(); }
    DemoBalloon(int cx, int cy, int cr) {
      _x = cx; _y = cy; _r = cr;
    }
    // Methods
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
  protected:
    void init() {
      _r = random(5, 10 + 1);
      _y = 63 + _r;
      _x = random(0, 128);
    }
  private:
    // Properties
    int _x;
    int _y;
    int _r;
};

const int numOfBalls = 4;

DemoBalloon balls[numOfBalls];

void setup() {
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
