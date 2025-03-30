#include "Pokerobo_Lab_Display_Handler.h"

class PingPongRacket {
  public:
    static const uint8_t WIDTH = 3;
    PingPongRacket(GeometryDisplayHandler* pen) {
      _pen = pen;
    }
    virtual void begin(uint8_t position=255, uint8_t size=20);
    virtual void move(JoystickAction *ctrl);
    virtual void draw();
    virtual bool hit(uint8_t x, uint8_t y);
    virtual uint8_t getX();
    uint8_t getY1();
    uint8_t getY2();
  protected:
    GeometryDisplayHandler* _pen = NULL;
    uint8_t _top = 0;
    uint8_t _size = 20;
};

class LPingPongRacket: public PingPongRacket {
  public:
    using PingPongRacket::PingPongRacket;
    void move(JoystickAction *ctrl);
    void draw();
    bool hit(uint8_t x, uint8_t y);
    uint8_t getX();
};

class RPingPongRacket: public PingPongRacket {
  public:
    using PingPongRacket::PingPongRacket;
    void move(JoystickAction *ctrl);
    void draw();
    bool hit(uint8_t x, uint8_t y);
    uint8_t getX();
};

void PingPongRacket::begin(uint8_t position, uint8_t size) {
  if (_size > 0 && _size < (63 + 1) / 2) {
    _size = size;
  }
  if (position <= 63 - _size + 1) {
    _top = position;
  } else {
    _top = random(0, 63 - _size);
  }
}

uint8_t PingPongRacket::getY1() {
  return _top;
}

uint8_t PingPongRacket::getY2() {
  return _top + _size;
}

void LPingPongRacket::draw() {
  _pen->drawBox(0, _top, WIDTH, _size);
}

void LPingPongRacket::move(JoystickAction *ctrl) {
  if (ctrl->isButtonPressed(MASK_THUMB_ON_UP)) {
    _top = (_top >= 3) ? _top - 3 : 0;
  }
  if (ctrl->isButtonPressed(MASK_THUMB_ON_DOWN)) {
    _top = (_top + 3 <= 63 - _size + 1) ? _top + 3 : 63 - _size + 1;
  }
}

bool LPingPongRacket::hit(uint8_t x, uint8_t y) {
  if (x > this->getX()) {
    return false;
  }
  if (y < this->getY1() || y > this->getY2()) {
    return false;
  }
  return true;
}

// x-axis of the racket surface
uint8_t LPingPongRacket::getX() {
  return WIDTH;
}

void RPingPongRacket::draw() {
  _pen->drawBox(127 - WIDTH + 1, _top, WIDTH, _size);
}

void RPingPongRacket::move(JoystickAction *ctrl) {
  if (ctrl->isButtonPressed(MASK_UP_BUTTON)) {
    _top = (_top >= 3) ? _top - 3 : 0;
  }
  if (ctrl->isButtonPressed(MASK_DOWN_BUTTON)) {
    _top = (_top + 3 <= 63 - _size + 1) ? _top + 3 : 63 - _size + 1;
  }
}

bool RPingPongRacket::hit(uint8_t x, uint8_t y) {
  if (x < this->getX()) {
    return false;
  }
  if (y < this->getY1() || y > this->getY2()) {
    return false;
  }
  return true;
}

// x-axis of the racket surface
uint8_t RPingPongRacket::getX() {
  return 127 - WIDTH;
}

//-------------------------------------------------------------------------------------------------

class PingPongGame {
  public:
    PingPongGame(GeometryDisplayHandler* pen);
    PingPongGame(GeometryDisplayHandler* pen, bool debug,
      LPingPongRacket *lRacket = NULL,
      RPingPongRacket *rRacket = NULL);
    void run(JoystickAction *ctrl, int delayTime=50);
    virtual void begin(uint8_t randomPin=A3);
    virtual void next(JoystickAction *ctrl);
    virtual void render();
    virtual void draw();
  private:
    GeometryDisplayHandler* _pen = NULL;
    LPingPongRacket *_lRacket = NULL;
    RPingPongRacket *_rRacket = NULL;
};

PingPongGame::PingPongGame(GeometryDisplayHandler* pen) {
  _pen = pen;
  _lRacket = new LPingPongRacket(_pen);
  _rRacket = new RPingPongRacket(_pen);
}

PingPongGame::PingPongGame(GeometryDisplayHandler* pen, bool debug,
    LPingPongRacket *lRacket,
    RPingPongRacket *rRacket
) {
  _pen = pen;
  _lRacket = (lRacket != NULL) ? lRacket : new LPingPongRacket(_pen);
  _rRacket = (rRacket != NULL) ? rRacket : new RPingPongRacket(_pen);
}

void PingPongGame::begin(uint8_t randomPin) {
  if (A0 <= randomPin && randomPin <= A5) {
    randomSeed(analogRead(randomPin));
  }
  _lRacket->begin();
  _rRacket->begin();
}

void PingPongGame::run(JoystickAction *ctrl, int delayTime) {
  next(ctrl);
  render();
  delay(delayTime);
}

void PingPongGame::next(JoystickAction *ctrl) {
  _lRacket->move(ctrl);
  _rRacket->move(ctrl);
}

void PingPongGame::render() {
  _pen->firstPage();
  do {
    draw();
  } while (_pen->nextPage());
}

void PingPongGame::draw() {
  _lRacket->draw();
  _rRacket->draw();
}

//-------------------------------------------------------------------------------------------------

JoystickAction action;
JoystickHandler han;
GeometryDisplayHandler pen;

PingPongGame game(&pen);

void setup() {
  Serial.begin(57600);
  han.begin();
  pen.begin();
  game.begin();
}

void loop() {
  game.run(han.input(&action), 100);
}
