#include "Pokerobo_Lab_Rolling_Wheel.h"

GeometryDisplayHandler dh;

int speed = 3;
byte direction = 1;
Wheel w(&dh);

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
