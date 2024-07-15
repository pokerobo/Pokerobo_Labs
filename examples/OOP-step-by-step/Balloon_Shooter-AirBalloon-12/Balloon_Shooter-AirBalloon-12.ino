#include "Pokerobo_Lab_Display_Handler.h"

#define TOTAL_OF_BALLOONS     10

GeometryDisplayHandler dh;

class DemoBalloon {
  public:
    // Constructors
    DemoBalloon() { init(); }
    DemoBalloon(int cx, int cy, int cr) {
      _x = cx; _y = cy; _r = cr;
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
    GeometryDisplayHandler *_pencil = NULL;
};

int numOfBalls = TOTAL_OF_BALLOONS;

DemoBalloon* balls[TOTAL_OF_BALLOONS] = { 0 };

void setup() {
  randomSeed(analogRead(A3));
  dh.begin();
  numOfBalls = random(3, TOTAL_OF_BALLOONS + 1);
  for(int k=0; k<numOfBalls; k++) {
    balls[k] = new DemoBalloon();
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
