#ifndef __POKEROBO_LAB_MPU_ACCEGYRO_RENDERER_H__
#define __POKEROBO_LAB_MPU_ACCEGYRO_RENDERER_H__

#include "Pokerobo_Lab_Display_Handler.h"

class AcceGyroRenderer {
  public:
    AcceGyroRenderer(GeometryDisplayHandler* pen = NULL);
    void setDisplayHandler(GeometryDisplayHandler* pen);
    void render();
    virtual bool update(int16_t value);
    virtual void draw();
  protected:
    void initialize();
    char* int2str_(char* buffer, int16_t value);
    int8_t valueToPoint(int16_t value);
    int16_t getValue();
    GeometryDisplayHandler* getDisplayHandler();
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


#define ACCE_DIAGRAM_SIZE 64

class AcceGyroDiagram: public AcceGyroRenderer {
  public:
    using AcceGyroRenderer::AcceGyroRenderer;
    bool update(int16_t value);
    void draw();
  private:
    int8_t points[ACCE_DIAGRAM_SIZE] = {0};
    int16_t _samples[ACCE_DIAGRAM_SIZE] = {0};
    int8_t _sample_head = 0;
    int8_t _sample_tail = ACCE_DIAGRAM_SIZE - 1;
    int8_t _sample_min = 0;
    int8_t _sample_max = 0;
};


class AcceGyroProgram: public ProgramSticker {
  public:
    AcceGyroProgram(AcceGyroRenderer *monitor, char *title = "AcceAnalyzer"): ProgramSticker(title) {
      _monitor = monitor;
    }
    int begin();
    int check(void* action, void* command=NULL);
    int close();
  private:
    AcceGyroRenderer *_monitor = NULL;
};

#endif
