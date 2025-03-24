#include "Pokerobo_Lab-9in1_Sensor_Shield-RGB_LED.h"

void RGBLEDHandler::begin() {
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
}

void RGBLEDHandler::write(byte r, byte g, byte b) {
  analogWrite(R_PIN, r);
  analogWrite(G_PIN, g);
  analogWrite(B_PIN, b);
}


RGBRandomizer::RGBRandomizer(byte deltaMax = 10, byte colorMax = 128) {
  _deltaMax = deltaMax;
  _colorMax = colorMax;
}

void RGBRandomizer::begin() {
  randomSeed(analogRead(A3));
}

void RGBRandomizer::randomRGB() {
  r = randomColor(r);
  g = randomColor(g);
  b = randomColor(b);
}

int RGBRandomizer::randomColor(int val) {
  int delta = map(random(0, 2*_deltaMax + 1), 0, 2*_deltaMax, -_deltaMax, _deltaMax);
  val = val + delta;
  if (val < 0) return 0;
  if (val > _colorMax) return _colorMax;
  return val;
}
