#include "Pokerobo_Lab_Display_Handler.h"

class SpaceShip {
  public:
    SpaceShip(GeometryDisplayHandler* pen) {
      _pen = pen;
    }
    virtual void draw();
  private:
    GeometryDisplayHandler* _pen = NULL;
    int _x = 63;
    int _y = 31;
};

void SpaceShip::draw() {
  _pen->drawTriangle(_x, _y - 7,
      _x - 7, _y,
      _x + 7, _y);
  _pen->drawTriangle(_x, _y - 1,
      _x - 5, _y + 4,
      _x + 5, _y + 4);
}

class AstroFire {
  public:
    AstroFire(GeometryDisplayHandler* pen) {
      _pen = pen;
      _spaceShip = new SpaceShip(_pen);
    }
    AstroFire(GeometryDisplayHandler* pen, SpaceShip* spaceShip) {
      _pen = pen;
      _spaceShip = (spaceShip != NULL) ? spaceShip : new SpaceShip(_pen);
    }
    void begin();
    void run(JoystickAction *ctrl, int delayTime=50);
    void next(JoystickAction *ctrl);
    void render();
    void draw();
  private:
    GeometryDisplayHandler* _pen = NULL;
    SpaceShip* _spaceShip = NULL;
};

void AstroFire::begin() {
}

void AstroFire::run(JoystickAction *ctrl, int delayTime) {
  next(ctrl);
  render();
  delay(delayTime);
}

void AstroFire::next(JoystickAction *ctrl) {
}

void AstroFire::render() {
  _pen->firstPage();
  do {
    draw();
  } while (_pen->nextPage());
}

void AstroFire::draw() {
  _spaceShip->draw();
}

JoystickAction action;
JoystickHandler joystickHandler;
GeometryDisplayHandler pen;

AstroFire game(&pen);

void setup() {
  Serial.begin(57600);
  joystickHandler.begin();
  pen.begin();
  game.begin();
}

void loop() {
  game.run(joystickHandler.input(&action));
}
