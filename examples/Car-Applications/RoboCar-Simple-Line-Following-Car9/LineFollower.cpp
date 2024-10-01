#include "LineFollower.h"

const int LineFollower::max_speed = 150;
const int LineFollower::medium_speed = 140;
const int LineFollower::min_speed = 110;

LineFollower::LineFollower(RoboCarHandler* roboCarHandler) {
  _roboCarHandler = roboCarHandler;
}

void LineFollower::begin() {
}

void LineFollower::check(uint8_t signals) {
  checkImplementation(signals);
}

void LineFollower::checkImplementation(uint8_t signals) {
  switch(signals) {
    case 0b10000:
    case 0b11000:
    case 0b11110:
      probe(0, min_speed, medium_speed, 1, 100);
      break;
    case 0b11100:
      probe(1, min_speed, medium_speed, 1, 100);
      break;
    case 0b01000:
    case 0b01100:
      probe(1, medium_speed, medium_speed, 1, 200);
      break;
    case 0b00100:
    case 0b01110:
      probe(1, medium_speed, medium_speed, 1, 200);
      break;
    case 0b00010:
    case 0b00110:
      probe(1, medium_speed, medium_speed, 1, 200);
      break;
    case 0b00111:
      probe(1, medium_speed, min_speed, 1, 100);
      break;
    case 0b00001:
    case 0b00011:
    case 0b01111:
      probe(1, medium_speed, min_speed, 0, 100);
      break;
    case 0b11111:
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
