#include "Pokerobo_Car.h"

class LineFollower {
  public:
    static const int max_speed;
    static const int medium_speed;
    static const int min_speed;
    LineFollower(RoboCarHandler* roboCarHandler);
    void begin();
    void check(uint8_t signals);
  protected:
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
    int _count = 0;
};

const int LineFollower::max_speed = 150;
const int LineFollower::medium_speed = 140;
const int LineFollower::min_speed = 110;

LineFollower::LineFollower(RoboCarHandler* roboCarHandler) {
  _roboCarHandler = roboCarHandler;
}

void LineFollower::begin() {
}

void LineFollower::check(uint8_t signals) {
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
      _count++;
      if (_count <= 10) {
        reverse();
        break;
      }
    default:
      _roboCarHandler->stop();
  }
}

void LineFollower::probe(int8_t leftDirection, int leftSpeed,
    int rightSpeed, int8_t rightDirection, uint32_t movingTime=200) {
  _count = 0;
  _leftDirection = leftDirection;
  _leftSpeed = leftSpeed;
  _rightDirection = rightDirection;
  _rightSpeed = rightSpeed;
  _movingTime = movingTime;
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

RoboCarHandler roboCarHandler;
LineFollower lineFollower(&roboCarHandler);
LineDetector5Channels lineDetector;

char text[9] = { 0 };

void setup() {
  Serial.begin(57600);

  roboCarHandler.begin();
  roboCarHandler.turnOn();
  lineDetector.setBlackLine(true);
  lineDetector.begin();
  lineFollower.begin();
}

void loop() {
  uint8_t signals = lineDetector.read();
  lineFollower.check(signals);
  Serial.println(lineDetector.toText(signals, text));
  delay(50);
}
