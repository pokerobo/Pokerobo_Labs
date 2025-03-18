#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler dh;

class Spoke {
  friend class Wheel;
  private:
    int no;
    int x;
    int y;
};

class Wheel {
  public:
    Wheel() {
      x = r;
      y = 63 - r;
      diameter = PI * r * 2;
      for(int i=0; i<6; i++) {
        spokes[i] = new Spoke();
      }
    };

    void swing(int speed, byte &direction) {
      if (direction) {
        x = x + speed;
        if (x > 127 - r) {
          x = 127 - r;
        }
        if (x == 127 - r) {
          direction = 1 - direction;
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
        if (x == r) {
          direction = 1 - direction;
        }
        distance = distance - speed;
        while (distance < 0.0) {
          distance = distance + diameter;
        }
      }
      for(int i=0; i<6/2; i++) {
        Spoke *s1 = spokes[i];
        float angle = 3.14159*i*360/6/180 + distance/r;
        s1->x = x + r*cos(angle);
        s1->y = y + r*sin(angle);
        Spoke *s2 = spokes[3 + i];
        s2->x = 2*x - s1->x;
        s2->y = 2*y - s1->y;
      }
    };

    void draw() {
      dh.drawCircle(x, y, r);
      for(int i=0; i<6; i++) {
        Spoke *spoke = spokes[i];
        dh.drawLine(x, y, spoke->x, spoke->y);
      }
    };

  private:
    int r = 15;
    int x = 0;
    int y = 0;
    float diameter = 0.0;
    float distance = 0.0;
    Spoke *spokes[6];
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
