#include "Pokerobo_Car.h"

const int max_speed = 150;
const int medium_speed = 140;
const int min_speed = 110;
const int moving_time = 100;
const int moving_time_2 = moving_time;
char text[9] = { 0 };

DisplayAdapter displayAdapter;
LineDetector5Channels lineDetector;
RoboCarHandler roboCarHandler;

int8_t _leftDirection = 0;
int _leftSpeed = 0;
int8_t _rightDirection = 0;
int _rightSpeed = 0;
uint32_t _movingTime = 0;

void nudge(int8_t leftDirection, int leftSpeed,
    int rightSpeed, int8_t rightDirection, uint32_t movingTime=200) {
  _leftDirection = leftDirection;
  _leftSpeed = leftSpeed;
  _rightDirection = rightDirection;
  _rightSpeed = rightSpeed;
  _movingTime = movingTime;
  roboCarHandler.move(_leftDirection, _leftSpeed, _rightSpeed, _rightDirection);
  if (_movingTime > 0) delay(_movingTime);
  roboCarHandler.move(0, _leftSpeed, _rightSpeed, 0);
}

void back(bool variant = false) {
  if (variant) {
    roboCarHandler.move(-_rightDirection, _rightSpeed, _leftSpeed, -_leftDirection);
  } else {
    roboCarHandler.move(-_leftDirection, _leftSpeed, _rightSpeed, -_rightDirection);
  }
  delay(_movingTime);
  roboCarHandler.move(_leftDirection, _leftSpeed, _rightSpeed, _rightDirection);
  delay(_movingTime/2);
  roboCarHandler.move(0, _leftSpeed, _rightSpeed, 0);
}

void setup() {
  Serial.begin(57600);

  displayAdapter.begin();
  lineDetector.begin();
  lineDetector.setBlackLine(true);
  roboCarHandler.begin();
  roboCarHandler.turnOn();
}

void loop() {
  uint8_t signals = lineDetector.read();
  switch(signals) {
    case 0b10000:
    case 0b11000:
    case 0b11110:
      nudge(0, min_speed, medium_speed, 1, moving_time);
      break;
    case 0b11100:
      nudge(1, min_speed, medium_speed, 1, moving_time);
      break;
    case 0b01000:
    case 0b01100:
      nudge(1, medium_speed, medium_speed, 1, moving_time_2);
      break;
    case 0b00100:
    case 0b01110:
      nudge(1, medium_speed, medium_speed, 1, moving_time_2);
      break;
    case 0b00010:
    case 0b00110:
      nudge(1, medium_speed, medium_speed, 1, moving_time_2);
      break;
    case 0b00111:
      nudge(1, medium_speed, min_speed, 1, moving_time);
      break;
    case 0b00001:
    case 0b00011:
    case 0b01111:
      nudge(1, medium_speed, min_speed, 0, moving_time);
      break;
    case 0b11111:
    case 0b00000:
      back();
      break;
    default:
      roboCarHandler.stop();
  }
  Serial.println(lineDetector.toText(signals, text));
  delay(50);
}
