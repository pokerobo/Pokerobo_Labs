#ifndef __POKEROBO_LAB_MPU_ACCEGYRO_RENDERER_H__
#define __POKEROBO_LAB_MPU_ACCEGYRO_RENDERER_H__

#include "Pokerobo_Lab_Display_Handler.h"

class AcceGyroRenderer {
  public:
    AcceGyroRenderer(GeometryDisplayHandler* pen = NULL);
    void setDisplayHandler(GeometryDisplayHandler* pen);
    void update(int16_t value);
    void draw();
  protected:
    void initialize();
    char* int2str_(char* buffer, int16_t value);
  private:
    GeometryDisplayHandler* _pen = NULL;
    uint8_t _charWidth = 5;
    int16_t _value = 0;
    int16_t _maxAcc = 25000;
    int16_t _minAcc = 12000;
    char _valueStr[7] = { 0 };
    char _minAccStr[7] = { 0 };
    char _maxAccStr[7] = { 0 };
};

#endif
