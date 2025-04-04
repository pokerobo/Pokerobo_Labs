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
    virtual void onJumpingBegin();
    virtual void onJumpingEnd();
    virtual void onSquattingBegin();
    virtual void onSquattingEnd();
};


class JumpingDetector {
  public:
    JumpingDetector(JumpingListener* listener, GeometryDisplayHandler* pen, AcceGyroRenderer* renderer) {
      _listener = listener;
      _pen = pen;
      _renderer = renderer;
      finishMillis = millis();
    }
    void update(int16_t ax, int16_t ay, int16_t az);
    void render();
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
    String stringify(motion_state_t state) {
      switch(state) {
        case MOTION_STATE_IDLE:
          return "idle";
        case MOTION_STATE_JUMPING_UP:
          return "jumping_up";
        case MOTION_STATE_JUMPING_DOWN:
          return "jumping_down";
        case MOTION_STATE_SQUATTING_DOWN:
          return "squatting_down";
        case MOTION_STATE_SQUATTING_UP:
          return "squatting_up";
      }
    }
    void logSwitchState_(motion_state_t next_state, int16_t az, bool auto_change=false) {
      if (auto_change) {
        Serial.print(" auto [");
      } else {
        Serial.print(" [");
      }
      Serial.print(stringify(getState()));
      Serial.print("]->[");
      Serial.print(stringify(next_state));
      Serial.print("] with az: ");
      Serial.println(az);
      if (next_state == MOTION_STATE_IDLE) {
        Serial.println();
      }
    }
};


class JumpingDetectorScreenLog: public JumpingDetector {
  public:
    using JumpingDetector::JumpingDetector;
    void showinfo();
  protected:
    String stringify(motion_state_t state);
    void logSwitchState_(motion_state_t next_state, int16_t az, bool auto_change=false);
  private:
    char lines[12][7] = { 0 };
};


class JumpingDemoProgram: public ProgramSticker {
  public:
    JumpingDemoProgram(JumpingDetector *detector, char *title = "Jumping Demo"): ProgramSticker(title) {
      _detector = detector;
    }
    int begin();
    int check(void* action, void* command=NULL);
    int close();
  private:
    JumpingDetector *_detector = NULL;
};

#endif
