#include "Pokerobo_Lab-9in1_Sensor_Shield-RGB_LED.h"

const int RANGE = 10;
const int LIMIT = 128;

RGBLEDHandler rgbLedHandler;

byte r = 50, g = 50, b = 50;

int randomColor(int val) {
  int delta = map(random(0, 2*RANGE + 1), 0, 2*RANGE, -RANGE, RANGE);
  val = val + delta;
  if (val < 0) return 0;
  if (val > LIMIT) return LIMIT;
  return val;
}

void setup() {
  Serial.begin(57600);
  randomSeed(analogRead(A3));
  rgbLedHandler.begin();
}

void loop() {
  r = randomColor(r);
  g = randomColor(g);
  b = randomColor(b);
  rgbLedHandler.write(r, g, b);
  delay(50);
}
