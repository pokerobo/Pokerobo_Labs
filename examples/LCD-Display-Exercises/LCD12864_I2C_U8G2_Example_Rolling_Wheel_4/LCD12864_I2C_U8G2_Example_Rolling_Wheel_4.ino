#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler dh;

const int halfTotalOfSpokes = 3;
const int totalOfSpokes = 2 * halfTotalOfSpokes;
const float angleBetweenSpokes = 3.14159*360/180/totalOfSpokes;

class Spoke {
  friend class Wheel;
  private:
    int no;
    int x;
    int y;
};

class Wheel {
  public:
    Wheel();
    void roll(int speed, byte direction);
    void swing(int speed, byte &direction);
    void draw();
  private:
    int r = 15;
    int x = 0;
    int y = 0;
    float diameter = 0.0;
    float distance = 0.0;
    Spoke *spokes[totalOfSpokes];
};

Wheel::Wheel() {
  x = r;
  y = dh.getMaxY() - r;
  diameter = PI * r * 2;
  for(int i=0; i<totalOfSpokes; i++) {
    spokes[i] = new Spoke();
  }
};

void Wheel::roll(int speed, byte direction) {
  int maxX = dh.getMaxX();
  if (direction) {
    x = x + speed;
    while (x > maxX - r) {
      x = maxX - r;
    }
    distance = distance + speed;
    while (distance >= diameter) {
      distance = distance - diameter;
    }
  } else {
    x = x - speed;
    if (x < r) {
      x = r;
    }
    distance = distance - speed;
    while (distance < 0.0) {
      distance = distance + diameter;
    }
  }
  for(int i=0; i<halfTotalOfSpokes; i++) {
    Spoke *s1 = spokes[i];
    float angle = i*angleBetweenSpokes + distance/r;
    s1->x = x + r*cos(angle);
    s1->y = y + r*sin(angle);
    Spoke *s2 = spokes[halfTotalOfSpokes + i];
    s2->x = 2*x - s1->x;
    s2->y = 2*y - s1->y;
  }
};

void Wheel::swing(int speed, byte &direction) {
  roll(speed, direction);
  int maxX = dh.getMaxX();
  if (direction) {
    if (x == maxX - r) {
      direction = 1 - direction;
    }
  } else {
    if (x == r) {
      direction = 1 - direction;
    }
  }
}

void Wheel::draw() {
  dh.drawCircle(x, y, r);
  dh.drawCircle(x, y, 2);
  for(int i=0; i<totalOfSpokes; i++) {
    Spoke *spoke = spokes[i];
    dh.drawLine(x, y, spoke->x, spoke->y);
  }
};

int speed = 3;
byte direction = 1;
Wheel w;

void setup() {
  Serial.begin(57600);
  dh.begin();
}

void loop() {
  w.swing(speed, direction);
  dh.firstPage();
  do {
    w.draw();
  } while(dh.nextPage());
  delay(50);
}
