#ifndef __POKEROBO_LAB_MPU_JUMPING_DETECTOR_H__
#define __POKEROBO_LAB_MPU_JUMPING_DETECTOR_H__

#include "Pokerobo_Lab_Display_Handler.h"
#include "Pokerobo_Lab_MPU_AcceGyroRenderer.h"

typedef enum {
  MOTION_STATE_IDLE = 0,
  MOTION_STATE_JUMPING_UP,
  MOTION_STATE_JUMPING_DOWN,
  MOTION_STATE_SQUATTING_DOWN,
  MOTION_STATE_SQUATTING_UP
} motion_state_t;


class JumpingListener {
  public:
    JumpingListener(bool serialLog = false);
    virtual void onJumpingBegin();
    virtual void onJumpingEnd();
    virtual void onSquattingBegin();
    virtual void onSquattingEnd();
  private:
    bool _serialLog = false;
};


class JumpingDetector {
  public:
    JumpingDetector(GeometryDisplayHandler* pen, AcceGyroRenderer* renderer, JumpingListener* listener = NULL) {
      _pen = pen;
      _renderer = renderer;
      _listener = (listener != NULL) ? listener : new JumpingListener();
      finishMillis = millis();
      initialize();
    }
    void update(int16_t ax, int16_t ay, int16_t az);
    void render();
    virtual void initialize();
    virtual void showinfo();
  protected:
    bool exceedThresholdTime();
    bool isWaitingTimeOver();
    bool isJumping();
    bool isSquatting();
    bool isIdle();
    motion_state_t getState();
    GeometryDisplayHandler* getDisplayHandler();
    virtual void logSwitchState_(motion_state_t next_state, int16_t az, bool auto_change=false);
  private:
    unsigned long finishMillis = 0;
    unsigned long lastMillis = 0;
    unsigned long actionThresholdTime = 300;
    motion_state_t _state = MOTION_STATE_IDLE;
    JumpingListener* _listener = NULL;
    GeometryDisplayHandler* _pen = NULL;
    AcceGyroRenderer* _renderer = NULL;
};


class JumpingDetectorSerialLog: public JumpingDetector {
  public:
    using JumpingDetector::JumpingDetector;
  protected:
    char* stringify(motion_state_t state);
    void logSwitchState_(motion_state_t next_state, int16_t az, bool auto_change=false);
};


#define JUMPING_LOG_TOTAL   5
#define JUMPING_LOG_LENGTH  15

class JumpingDetectorScreenLog: public JumpingDetector {
  public:
    using JumpingDetector::JumpingDetector;
    void initialize();
    void showinfo();
  protected:
    char* stringify(motion_state_t state);
    void logSwitchState_(motion_state_t next_state, int16_t az, bool auto_change=false);
    void lineFeed_();
  private:
    uint8_t _charHeight = 8;
    uint8_t _charWidth = 5;
    char _lines[JUMPING_LOG_TOTAL][JUMPING_LOG_LENGTH] = { 0 };
    int8_t _line_tail = 0;
    int8_t _line_head = 0;
};


class JumpingDemoProgram: public ProgramSticker {
  public:
    JumpingDemoProgram(JumpingDetector *detector, char *title = "Jumping Demo");
    int begin();
    int check(void* action, void* command=NULL);
    int close();
  private:
    JumpingDetector *_detector = NULL;
};

#endif
