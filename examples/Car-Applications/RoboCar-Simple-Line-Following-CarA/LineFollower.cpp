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
}

void LineFollower::check(uint8_t signals) {
  decideNextMove(signals);
}

void LineFollower::decideNextMove(uint8_t signals) {
  // check to turn on the car
  if (!_roboCarHandler->isActive() && signals == 0b11111) {
    if (_idleCount < 255) {
      _idleCount++;
    }
    if (_idleCount >= 50) {
      _roboCarHandler->turnOn();
    }
  } else {
    _idleCount = 0;
  }
  // if the car is not active, do nothing
  if (!_roboCarHandler->isActive()) {
    return;
  }
  // check the car has been at finish line
  if (signals == 0b11111) {
    _roboCarHandler->turnOff();
    _isFinished = true;
  }
  // if the car is not active, do nothing
  if (!_roboCarHandler->isActive()) {
    return;
  }
  // decide the next move
  switch(signals) {
    case 0b10000:
    case 0b11000:
    case 0b11110:
      probe(0, _stepMinSpeed, _stepMediumSpeed, 1, _stepMovingTime);
      break;
    case 0b11100:
      probe(1, _stepMinSpeed, _stepMediumSpeed, 1, _stepMovingTime);
      break;
    case 0b01000:
    case 0b01100:
      probe(1, _stepMediumSpeed, _stepMediumSpeed, 1, _stepMovingTime_2);
      break;
    case 0b00100:
    case 0b01110:
      probe(1, _stepMediumSpeed, _stepMediumSpeed, 1, _stepMovingTime_2);
      break;
    case 0b00010:
    case 0b00110:
      probe(1, _stepMediumSpeed, _stepMediumSpeed, 1, _stepMovingTime_2);
      break;
    case 0b00111:
      probe(1, _stepMediumSpeed, _stepMinSpeed, 1, _stepMovingTime);
      break;
    case 0b00001:
    case 0b00011:
    case 0b01111:
      probe(1, _stepMediumSpeed, _stepMinSpeed, 0, _stepMovingTime);
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

void LineFollower::probe(int8_t leftDirection, int leftSpeed,
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
