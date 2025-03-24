#include "Pokerobo_Lab-9in1_Sensor_Shield-RGB_LED.h"

RGBLEDHandler rgbLedHandler;

void setup() {
  Serial.begin(57600);
  rgbLedHandler.begin();
}

void loop() {
  int val = map(analogRead(A0), 0, 1023, 0, 255);

  Serial.print("Rotation value: ");
  Serial.print(val);

  rgbLedHandler.write(val, val, val);

  delay(500);
}
