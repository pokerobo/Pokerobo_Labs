#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler dh;

class DemoBalloon {
  public:
    DemoBalloon() {}
    DemoBalloon(int cx, int cy, int cr) {
      _x = cx; _y = cy; _r = cr;
    }
    void init(GeometryDisplayHandler *displayHandler) {
      _r = random(5, 10 + 1);
      _y = 63 + _r;
      _x = random(0, 128);
      _pencil = displayHandler;
    }
    // method / phương thức / hành vi
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
    // Properties / thuộc tính
    int _x;
    int _y;
    int _r;
    GeometryDisplayHandler *_pencil = NULL;
};

const int numOfBalls = 4;

// balls không còn là một mảng các đối tượng kiểu DemoBalloon
// balls bây giờ là một mảng các con trỏ (có thể trỏ tới các) đối tượng DemoBalloon
DemoBalloon* balls[numOfBalls];

void setup() {
  randomSeed(analogRead(A3));
  dh.begin();
  for(int k=0; k<numOfBalls; k++) {
    balls[k] = new DemoBalloon();
    // -> toán tử tham chiếu
    // _x có phải là thuộc tính của balls[k]? NO
    // _x là thuộc tính của đối tượng mà balls[k] trỏ đến
    balls[k]->init(&dh);
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
