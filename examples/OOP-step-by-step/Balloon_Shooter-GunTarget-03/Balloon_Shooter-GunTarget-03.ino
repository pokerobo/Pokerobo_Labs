#include "Pokerobo_Lab_Display_Handler.h"

JoystickAction action;
JoystickHandler joystickHandler;
GeometryDisplayHandler displayHandler;

class DemoGunTarget {
  public:
    int getX() { return x; }
    int getY() { return y; }

    int speedOfX(int jX) {
      int dX = -512 + jX; // jX - 512
      if (abs(dX) < 30) dX = 0;
      return map(dX, -512, 512, -10, 10);
    }

    int speedOfY(int jY) {
      int dY = -512 + jY; // jY - 512
      if (abs(dY) < 30) dY = 0;
      return map(dY, -512, 512, 10, -10);
    }

    void move(int dX, int dY) {
      x = x + dX > 0 ? (x + dX <= 127 ? x + dX : 127) : 0;
      y = (y + dY > 0) ? (y + dY <= 63 ? y + dY : 63) : 0;
    }

    void update(int jX, int jY) {
      move(speedOfX(jX), speedOfY(jY));
    }

    void draw() {
      displayHandler.drawPixel(x, y);
      displayHandler.drawCircle(x, y, r);
    }
  private:
    int x;
    int y;
    int r = 3;
};

DemoGunTarget gunTarget;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
  joystickHandler.begin();
}

void loop() {
  joystickHandler.input(&action);

  gunTarget.update(action.getX(), action.getY());

  displayHandler.firstPage();
  do {
    gunTarget.draw();
  } while(displayHandler.nextPage());

  delay(50);
}
