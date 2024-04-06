#include <U8g2lib.h>

U8G2_ST7567_ENH_DG128064I_1_HW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

class Bubble {
  public:
    Bubble();
    Bubble(int8_t _x, int8_t _y, int8_t _r);
    int8_t x;
    int8_t y;
    int8_t r;
    bool isDisappeared();
    int8_t getSpeed();
};

Bubble::Bubble() {
  x = 0;
  y = 0;
  r = 10;
}

Bubble::Bubble(int8_t _x, int8_t _y = 64+10, int8_t _r = 10) {
  x = _x;
  y = _y;
  r = _r;
}

bool Bubble::isDisappeared() {
  return this->y < -this->r;
}

int8_t Bubble::getSpeed() {
  if (this->r > 8) return 4;
  if (this->r > 5) return 3;
  return 2;
}

class Aquarium {
  public:
    Aquarium(uint8_t _total);
    uint8_t total = 0;
    Bubble bubbles[10];
    void begin();
    void change();
    void render();
};

Aquarium::Aquarium(uint8_t _total) {
  total = _total;
}

void Aquarium::begin() {
  randomSeed(analogRead(A3));
  for (uint8_t i=0; i<total; i++) {
    Bubble *b = &bubbles[i];
    b->r = random(5, 10 + 1);
    b->x = random(127);
    b->y = random(b->r + 63 + 1);
  }
}

void Aquarium::change() {
  for (uint8_t i=0; i<total; i++) {
    Bubble *b = &bubbles[i];
    if (!b->isDisappeared()) {
      b->y -= b->getSpeed();
    } else {
      b->r = random(5, 10 + 1);
      b->x = random(127);
      b->y = b->r + 63 + 1;
    }
  }
}

void Aquarium::render() {
  for (uint8_t i=0; i<total; i++) {
    Bubble *b = &bubbles[i];
    u8g2.drawCircle(b->x, b->y, b->r, U8G2_DRAW_ALL);
  }
}

Aquarium aquarium(5);

void setup() {
  u8g2.setI2CAddress(0x3F * 2); 
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  Serial.begin(57600);
  aquarium.begin();
}

void loop() {
  aquarium.change();
  drawBubbles();
  delay(50);
}

void drawBubbles() {
  u8g2.firstPage();
  do {
    aquarium.render();
  } while (u8g2.nextPage());
}
