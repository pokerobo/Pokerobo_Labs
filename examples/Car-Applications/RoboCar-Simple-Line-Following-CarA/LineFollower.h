#ifndef __POKEROBO_LAB_LINE_FOLLOWER_H__
#define __POKEROBO_LAB_LINE_FOLLOWER_H__

#include "Pokerobo_Car.h"

#define LF_STEP_MAX_SPEED               150
#define LF_STEP_MEDIUM_SPEED            140
#define LF_STEP_MIN_SPEED               110
#define LF_STEP_MOVING_TIME              50

class LineFollower {
  public:
    LineFollower(RoboCarHandler* roboCarHandler);
    void begin(
        int stepMaxSpeed = LF_STEP_MAX_SPEED,
        int stepMediumSpeed = LF_STEP_MEDIUM_SPEED,
        int stepMinSpeed = LF_STEP_MIN_SPEED,
        int stepMovingTime = LF_STEP_MOVING_TIME);
    void check(uint8_t signals);
  protected:
    virtual void decideNextMove(uint8_t signals);
    virtual void remember(int8_t leftDirection, int leftSpeed,
        int rightSpeed, int8_t rightDirection, uint32_t movingTime=200);
    virtual void nudge(int8_t leftDirection, int leftSpeed,
        int rightSpeed, int8_t rightDirection, uint32_t movingTime=200);
    virtual void reverse(bool variant=false);
  private:
    RoboCarHandler* _roboCarHandler = NULL;
    int _stepMaxSpeed = LF_STEP_MAX_SPEED;
    int _stepMediumSpeed = LF_STEP_MEDIUM_SPEED;
    int _stepMinSpeed = LF_STEP_MIN_SPEED;
    int _stepMovingTime = LF_STEP_MOVING_TIME;
    int _stepMovingTime_2 = LF_STEP_MOVING_TIME;
    int8_t _leftDirection = 0;
    int _leftSpeed = 0;
    int8_t _rightDirection = 0;
    int _rightSpeed = 0;
    uint32_t _movingTime = 0;
    int _reversionCount = 0;
    byte _idleCount = 0;
    bool _isFinished = false;
};

#endif
