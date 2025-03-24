#include "Pokerobo_Lab-9in1_Sensor_Shield-Light_Sensor.h"

LightSensor lightSensor;

void setup() {
  Serial.begin(57600);
  lightSensor.begin();
}

void loop() {
  lightSensor.print();
  delay(500);
}
