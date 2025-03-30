#include "Pokerobo_Lab_Display_Handler.h"

class Dinosaur {
  public:
    Dinosaur(GeometryDisplayHandler* pen) {
      _pen = pen;
    }
    virtual void draw();
  private:
    GeometryDisplayHandler* _pen = NULL;
    int _x = 63;
    int _y = 31;
};

void Dinosaur::draw() {
  
}

class DinoRacerGame {
  public:
    DinoRacerGame(GeometryDisplayHandler* pen) {
      _pen = pen;
      _dinosaur = new Dinosaur(_pen);
    }
    DinoRacerGame(GeometryDisplayHandler* pen, Dinosaur* dinosaur) {
      _pen = pen;
      _dinosaur = (dinosaur != NULL) ? dinosaur : new Dinosaur(_pen);
    }
    void begin();
    void run(JoystickAction *ctrl, int delayTime=50);
    void next(JoystickAction *ctrl);
    void render();
    void draw();
  private:
    GeometryDisplayHandler* _pen = NULL;
    Dinosaur* _dinosaur = NULL;
};

void DinoRacerGame::begin() {
}

void DinoRacerGame::run(JoystickAction *ctrl, int delayTime) {
  next(ctrl);
  render();
  delay(delayTime);
}

void DinoRacerGame::next(JoystickAction *ctrl) {
}

void DinoRacerGame::render() {
  _pen->firstPage();
  do {
    draw();
  } while (_pen->nextPage());
}

void DinoRacerGame::draw() {
  _dinosaur->draw();
}

JoystickAction action;
JoystickHandler joystickHandler;
GeometryDisplayHandler pen;

DinoRacerGame game(&pen);

void setup() {
  Serial.begin(57600);
  joystickHandler.begin();
  pen.begin();
  game.begin();
}

void loop() {
  game.run(joystickHandler.input(&action));
}
