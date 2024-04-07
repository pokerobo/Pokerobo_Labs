#ifndef __POKEROBO_LIB_WATER_BUBBLE_H__
#define __POKEROBO_LIB_WATER_BUBBLE_H__

#include <Arduino.h>

#ifndef WATER_BUBBLES_TOTAL
#define WATER_BUBBLES_TOTAL  10
#endif//WATER_BUBBLES_TOTAL

class Bubble {
  public:
    Bubble();
    Bubble(int8_t _x, int8_t _y, int8_t _r);
    int8_t x;
    int8_t y;
    int8_t r;
    bool isDisappeared();
    int8_t getSpeed();
};

class Aquarium {
  public:
    Aquarium(void* u8g2Ref, uint8_t total);
    void begin();
    void change();
    void render();
  private:
    uint8_t _total = 0;
    Bubble _bubbles[WATER_BUBBLES_TOTAL];
    void* _u8g2Ref;
};

#endif
