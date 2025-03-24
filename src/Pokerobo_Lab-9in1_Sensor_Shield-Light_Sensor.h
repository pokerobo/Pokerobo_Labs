#ifndef __POKEROBO_LAB_9IN1_SENSOR_SHIELD_LIGHT_SENSOR_H__
#define __POKEROBO_LAB_9IN1_SENSOR_SHIELD_LIGHT_SENSOR_H__

#include <Arduino.h>

typedef enum LIGHT_SENSOR_LEVEL {
  LIGHT_LEVEL_DARK,
  LIGHT_LEVEL_DIM,
  LIGHT_LEVEL_LIGHT,
  LIGHT_LEVEL_BRIGHT,
  LIGHT_LEVEL_DAZZLING,
} light_sensor_level_t;

class LightSensor {
  public:
    void begin();
    virtual light_sensor_level_t read();
    virtual void print(light_sensor_level_t lightLevel);
    void print();
  protected:
    virtual light_sensor_level_t threshhold(int value);
};

#endif
