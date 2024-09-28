#include "Pokerobo_Car.h"

const int max_speed = 150;
const int medium_speed = 140;
const int min_speed = 110;
char text[9] = { 0 };

DisplayAdapter displayAdapter;
LineDetector5Channels lineDetector;
RoboCarHandler roboCarHandler;

void probe(int8_t leftDirection, int leftSpeed, int rightSpeed, int8_t rightDirection, uint32_t delayTime=200) {
  roboCarHandler.move(leftDirection, leftSpeed, rightSpeed, rightDirection);
  if (delayTime > 0) delay(delayTime);
  roboCarHandler.move(0, leftSpeed, rightSpeed, 0);
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
      probe(0, min_speed, medium_speed, 1);
      break;
    case 0b11100:
      probe(1, min_speed, medium_speed, 1);
      break;
    case 0b01000:
    case 0b01100:
      probe(1, medium_speed, medium_speed, 1);
      break;
    case 0b00100:
    case 0b01110:
      probe(1, medium_speed, medium_speed, 1);
      break;
    case 0b00010:
    case 0b00110:
      probe(1, medium_speed, medium_speed, 1);
      break;
    case 0b00111:
      probe(1, medium_speed, min_speed, 1);
      break;
    case 0b00001:
    case 0b00011:
      probe(1, medium_speed, min_speed, 0);
      break;
    default:
      roboCarHandler.stop();
  }
  Serial.println(lineDetector.toText(signals, text));
  delay(50);
}
