#ifndef __POKEROBO_LAB_LINE_FOLLOWER_H__
#define __POKEROBO_LAB_LINE_FOLLOWER_H__

#include "Pokerobo_Car.h"

class LineFollower {
  public:
    static const int max_speed;
    static const int medium_speed;
    static const int min_speed;
    static const int moving_time;
    static const int moving_time_2;
    LineFollower(RoboCarHandler* roboCarHandler);
    void begin();
    void check(uint8_t signals);
  protected:
    virtual void decideNextMove(uint8_t signals);
    virtual void remember(int8_t leftDirection, int leftSpeed,
        int rightSpeed, int8_t rightDirection, uint32_t movingTime=200);
    virtual void probe(int8_t leftDirection, int leftSpeed,
        int rightSpeed, int8_t rightDirection, uint32_t movingTime=200);
    virtual void reverse(bool variant=false);
  private:
    RoboCarHandler* _roboCarHandler = NULL;
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
