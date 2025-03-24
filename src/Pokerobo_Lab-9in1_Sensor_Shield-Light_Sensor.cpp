#include "Pokerobo_Lab-9in1_Sensor_Shield-Light_Sensor.h"

void LightSensor::begin() { }

light_sensor_level_t LightSensor::read() {
  return threshhold(analogRead(A1));
}

light_sensor_level_t LightSensor::threshhold(int value) {
  if (value < 10) {
    return LIGHT_SENSOR_LEVEL::LIGHT_LEVEL_DARK;
  } else if (value < 200) {
    return LIGHT_SENSOR_LEVEL::LIGHT_LEVEL_DIM;
  } else if (value < 500) {
    return LIGHT_SENSOR_LEVEL::LIGHT_LEVEL_LIGHT;
  } else if (value < 800) {
    return LIGHT_SENSOR_LEVEL::LIGHT_LEVEL_BRIGHT;
  } else {
    return LIGHT_SENSOR_LEVEL::LIGHT_LEVEL_DAZZLING;
  }
}

void LightSensor::print(light_sensor_level_t lightLevel) {
  switch (lightLevel) {
    case LIGHT_SENSOR_LEVEL::LIGHT_LEVEL_DARK:
      Serial.println(" - Dark");
    case LIGHT_SENSOR_LEVEL::LIGHT_LEVEL_DIM:
      Serial.println(" - Dim");
    case LIGHT_SENSOR_LEVEL::LIGHT_LEVEL_LIGHT:
      Serial.println(" - Light");
    case LIGHT_SENSOR_LEVEL::LIGHT_LEVEL_BRIGHT:
      Serial.println(" - Bright");
    case LIGHT_SENSOR_LEVEL::LIGHT_LEVEL_DAZZLING:
      Serial.println(" - Dazzling");
  }
}

void LightSensor::print() {
  return print(read());
}
