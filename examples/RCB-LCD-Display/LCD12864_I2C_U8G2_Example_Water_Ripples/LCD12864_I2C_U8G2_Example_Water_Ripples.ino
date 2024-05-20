#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
}

byte r0=0, r1=0, r2=0, r3=0, r4=0, r5=0;

void move(byte &x, byte &y) {
  if (x == 15) {
    y = 0;
  }
  y += 3;
  if (y >= 63) {
    y = 0;
  }
}

void loop() {
  move(r0, r1);
  move(r1, r2);
  move(r2, r3);
  move(r3, r4);
  move(r4, r5);

  displayHandler.firstPage();
  do {
    displayHandler.drawCircle(63, 31, r1);
    displayHandler.drawCircle(63, 31, r2);
    displayHandler.drawCircle(63, 31, r3);
    displayHandler.drawCircle(63, 31, r4);
    displayHandler.drawCircle(63, 31, r5);
    displayHandler.drawDisc(63, 31, 10);
  } while (displayHandler.nextPage());

  delay(300);
}
