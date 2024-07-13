#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler dh;

class DemoBalloon {
  public:
    // Constructors
    DemoBalloon() {}
    DemoBalloon(int cx, int cy, int cr) {
      _x = cx; _y = cy; _r = cr;
    }
    void init() {
      _r = random(5, 10 + 1);
      _y = 63 + _r;
      _x = random(0, 128);
    }
    void set(GeometryDisplayHandler *displayHandler) {
      _pencil = displayHandler;
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
      _pencil->drawCircle(_x, _y, _r);  
    }
  private:
    // Properties
    int _x;
    int _y;
    int _r;
    GeometryDisplayHandler *_pencil = NULL;
};

const int numOfBalls = 4;

DemoBalloon* balls[numOfBalls];

void setup() {
  randomSeed(analogRead(A3));
  dh.begin();
  for(int k=0; k<numOfBalls; k++) {
    balls[k] = new DemoBalloon();
    balls[k]->init();
    balls[k]->set(&dh);
  }
}

void loop() {
  for(int i=0; i<numOfBalls; i++) {
    balls[i]->check();
  }

  dh.firstPage();
  do {
    for(int i=0; i<numOfBalls; i++) {
      balls[i]->draw();
    }
  } while(dh.nextPage());

  delay(50);
}
