#ifndef __POKEROBO_LAB_9IN1_SENSOR_SHIELD_RGB_LED_H__
#define __POKEROBO_LAB_9IN1_SENSOR_SHIELD_RGB_LED_H__

#include <Arduino.h>

const int R_PIN =  9; // select the pin for the red LED
const int G_PIN = 10; // select the pin for the green LED
const int B_PIN = 11; // select the pin for the  blue LED

class RGBLEDHandler {
  public:
    void begin();
    void write(byte r, byte g, byte b);
};

class RGBRandomizer {
  public:
    RGBRandomizer(byte deltaMax = 10, byte colorMax = 128);
    void begin();
    void randomRGB();
    byte r = 50;
    byte g = 50;
    byte b = 50;
  private:
    byte _deltaMax = 10;
    byte _colorMax = 255;
    int randomColor(int val);
};

#endif
