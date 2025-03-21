#include "LineFollower.h"

LineFollower::LineFollower(RoboCarHandler* roboCarHandler) {
  _roboCarHandler = roboCarHandler;
}

void LineFollower::begin(
      int stepMaxSpeed,
      int stepMediumSpeed,
      int stepMinSpeed,
      int stepMovingTime) {
  _stepMaxSpeed = stepMaxSpeed;
  _stepMediumSpeed = stepMediumSpeed;
  _stepMinSpeed = stepMinSpeed;
  _stepMovingTime = stepMovingTime;
  _stepMovingTime_2 = _stepMovingTime;
  _roboCarHandler->turnOn();
}

void LineFollower::check(uint8_t signals) {
  decideNextMove(signals);
}

void LineFollower::decideNextMove(uint8_t signals) {
  // decide the next move
  switch(signals) {
    case 0b10000:
    case 0b11000:
    case 0b11110:
      nudge(0, _stepMinSpeed, _stepMediumSpeed, 1, _stepMovingTime);
      break;
    case 0b11100:
      nudge(1, _stepMinSpeed, _stepMediumSpeed, 1, _stepMovingTime);
      break;
    case 0b01000:
    case 0b01100:
      nudge(1, _stepMediumSpeed, _stepMediumSpeed, 1, _stepMovingTime_2);
      break;
    case 0b00100:
    case 0b01110:
      nudge(1, _stepMediumSpeed, _stepMediumSpeed, 1, _stepMovingTime_2);
      break;
    case 0b00010:
    case 0b00110:
      nudge(1, _stepMediumSpeed, _stepMediumSpeed, 1, _stepMovingTime_2);
      break;
    case 0b00111:
      nudge(1, _stepMediumSpeed, _stepMinSpeed, 1, _stepMovingTime);
      break;
    case 0b00001:
    case 0b00011:
    case 0b01111:
      nudge(1, _stepMediumSpeed, _stepMinSpeed, 0, _stepMovingTime);
      break;
    case 0b00000:
      _reversionCount++;
      if (_reversionCount <= 10) {
        reverse();
        break;
      }
    default:
      _roboCarHandler->stop();
  }
}

void LineFollower::remember(int8_t leftDirection, int leftSpeed,
    int rightSpeed, int8_t rightDirection, uint32_t movingTime=200) {
  _leftDirection = leftDirection;
  _leftSpeed = leftSpeed;
  _rightDirection = rightDirection;
  _rightSpeed = rightSpeed;
  _movingTime = movingTime;
}

void LineFollower::nudge(int8_t leftDirection, int leftSpeed,
    int rightSpeed, int8_t rightDirection, uint32_t movingTime=200) {
  remember(leftDirection, leftSpeed, rightSpeed, rightDirection, movingTime);
  _reversionCount = 0;
  _roboCarHandler->move(_leftDirection, _leftSpeed, _rightSpeed, _rightDirection);
  if (_movingTime > 0) delay(_movingTime);
  _roboCarHandler->move(0, _leftSpeed, _rightSpeed, 0);
}

void LineFollower::reverse(bool variant) {
  if (variant) {
    _roboCarHandler->move(-_rightDirection, _rightSpeed, _leftSpeed, -_leftDirection);
  } else {
    _roboCarHandler->move(-_leftDirection, _leftSpeed, _rightSpeed, -_rightDirection);
  }
  delay(_movingTime);
  _roboCarHandler->move(_leftDirection, _leftSpeed, _rightSpeed, _rightDirection);
  delay(_movingTime/2);
  _roboCarHandler->move(0, _leftSpeed, _rightSpeed, 0);
}
