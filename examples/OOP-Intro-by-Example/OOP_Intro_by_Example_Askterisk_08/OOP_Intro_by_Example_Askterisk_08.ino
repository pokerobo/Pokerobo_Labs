#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

JoystickHandler joystickHandler;
JoystickAction joystickControl;

int gt0(int v) {
  return (v > 0) ? v : 0;
}

class Asterisk {
  public:
    Asterisk(JoystickHandler* joystickHandler,
        GeometryDisplayHandler* displayHandler,
        int radius = 20) {
      this->joystickHandler = joystickHandler;
      _displayHandler = displayHandler;
      this->radius = radius;
    }
    void followJoystick() {
      JoystickAction joystickControl;
      joystickHandler->input(&joystickControl);
      followJoystick(joystickControl.getX(), joystickControl.getY());
    }
    void followJoystick(int joystickX, int joystickY) {
      x = map(joystickX, 0, 1023, 0, 127);
      y = map(joystickY, 0, 1023, 63,  0);
    }
    void draw() {
      _displayHandler->drawLine(x, gt0(y - radius), x, y + radius);
      _displayHandler->drawLine(gt0(x - radius), y, x + radius, y);

      int len2 = radius / sqrt(2);
      int cutx = min(len2, x);
      int cuty = min(len2, y);
      int cutz = min(cutx, cuty);

      _displayHandler->drawLine(x - cutz, y - cutz, x + len2, y + len2);
      _displayHandler->drawLine(x - cutx, y + cutx, x + cuty, y - cuty);
    }
  private:
    JoystickHandler* joystickHandler;
    GeometryDisplayHandler* _displayHandler;
    int radius = 20;
    int x = 0;
    int y = 0;
};

Asterisk asterisk(&joystickHandler, &displayHandler, 15);

void setup() {
  Serial.begin(57600);
  joystickHandler.begin();
  displayHandler.begin();
}

void loop() {
  asterisk.followJoystick();
  displayHandler.firstPage();
  do {
    asterisk.draw();
  } while (displayHandler.nextPage());
}
