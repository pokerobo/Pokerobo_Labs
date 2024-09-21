#include "Pokerobo_Car.h"

const int max_speed = 180;
const int medium_speed = 140;
const int min_speed = 100;

char text[9] = { 0 };

DisplayAdapter displayAdapter;
LineDetector5Channels lineDetector;
RoboCarHandler roboCarHandler;

void setup() {
  Serial.begin(57600);

  displayAdapter.begin();
  lineDetector.begin();
  lineDetector.setBlackLine(false);
  roboCarHandler.begin();
  roboCarHandler.turnOn();
}

void loop() {
  uint8_t signals = lineDetector.read();
  switch(signals) {
    case 0b10000:
    case 0b11000:
      roboCarHandler.move(1, min_speed, max_speed, 1);
      break;
    case 0b01100:
    case 0b11100:
      roboCarHandler.move(1, min_speed, medium_speed, 1);
      break;
    case 0b01110:
      roboCarHandler.move(1, max_speed, max_speed, 1);
      break;
    case 0b00110:
    case 0b00111:
      roboCarHandler.move(1, medium_speed, min_speed, 1);
      break;
    case 0b00011:
    case 0b00001:
      roboCarHandler.move(1, max_speed, min_speed, 1);
      break;
    case 0b11111:
    case 0b00000:
      roboCarHandler.stop();
      break;
  }
  Serial.println(lineDetector.toText(signals, text));
  delay(200);
}
