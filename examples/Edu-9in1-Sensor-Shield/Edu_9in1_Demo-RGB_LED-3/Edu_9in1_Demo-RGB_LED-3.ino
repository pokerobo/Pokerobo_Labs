#include "Pokerobo_Lab-9in1_Sensor_Shield-RGB_LED.h"

RGBLEDHandler rgbLedHandler;
RGBRandomizer rgbRandomizer;

void setup() {
  Serial.begin(57600);
  rgbLedHandler.begin();
  rgbRandomizer.begin();
}

void loop() {
  rgbRandomizer.randomRGB();
  rgbLedHandler.write(rgbRandomizer.r, rgbRandomizer.g, rgbRandomizer.b);
  delay(50);
}
