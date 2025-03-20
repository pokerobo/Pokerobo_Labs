#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

class Bubble {
  friend class Aquarium;
  public:
    Bubble();
    Bubble(int8_t x, int8_t y, int8_t r);
    int8_t _x;
    int8_t _y;
    int8_t _r;
    bool isDisappeared();
    int8_t getSpeed();
};

Bubble::Bubble() {
  _x = 0;
  _y = 0;
  _r = 10;
}

Bubble::Bubble(int8_t x, int8_t y = 64+10, int8_t r = 10) {
  _x = x;
  _y = y;
  _r = r;
}

bool Bubble::isDisappeared() {
  return this->_y < -this->_r;
}

int8_t Bubble::getSpeed() {
  if (this->_r > 8) return 4;
  if (this->_r > 5) return 3;
  return 2;
}

class Aquarium {
  public:
    Aquarium(uint8_t total);
    uint8_t _total = 0;
    Bubble bubbles[10];
    void begin();
    void change();
    void render();
};

Aquarium::Aquarium(uint8_t total) {
  _total = total;
}

void Aquarium::begin() {
  randomSeed(analogRead(A3));
  for (uint8_t i=0; i<_total; i++) {
    Bubble *b = &bubbles[i];
    b->_r = random(5, 10 + 1);
    b->_x = random(127);
    b->_y = random(b->_r + 63 + 1);
  }
}

void Aquarium::change() {
  for (uint8_t i=0; i<_total; i++) {
    Bubble *b = &bubbles[i];
    if (!b->isDisappeared()) {
      b->_y -= b->getSpeed();
    } else {
      b->_r = random(5, 10 + 1);
      b->_x = random(127);
      b->_y = b->_r + 63 + 1;
    }
  }
}

void Aquarium::render() {
  for (uint8_t i=0; i<_total; i++) {
    Bubble *b = &bubbles[i];
    displayHandler.drawCircle(b->_x, b->_y, b->_r);
  }
}

Aquarium aquarium(5);

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
  aquarium.begin();
}

void loop() {
  aquarium.change();
  drawBubbles();
  delay(50);
}

void drawBubbles() {
  displayHandler.firstPage();
  do {
    aquarium.render();
  } while (displayHandler.nextPage());
}
