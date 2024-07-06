#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler dh;

class DemoBalloon {
  public:
    DemoBalloon() {}
    DemoBalloon(int cx, int cy, int cr) {
      _x = cx; _y = cy; _r = cr;
    }
    // method / phương thức / hành vi
    void init() {
      _r = random(5, 10 + 1);
      _x = random(0, 128);
      _y = 63;
    }
    void check() {
      if (_y + _r >= 0) {
        _y = _y - 3;
      } else {
        _y = 63;
        _x = random(0, 128);
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
    balls[k]->init();
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
