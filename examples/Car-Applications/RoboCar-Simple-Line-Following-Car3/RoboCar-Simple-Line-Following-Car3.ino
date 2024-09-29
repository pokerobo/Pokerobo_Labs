#include "Pokerobo_Car.h"

const int max_speed = 150;
const int medium_speed = 130;
const int min_speed = 90;
char text[9] = { 0 };

DisplayAdapter displayAdapter;
LineDetector5Channels lineDetector;
RoboCarHandler roboCarHandler;

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
      roboCarHandler.move(0, min_speed, medium_speed, 1);
      delay(200);
      roboCarHandler.move(0, min_speed, medium_speed, 0);
      break;
    case 0b11100:
      roboCarHandler.move(1, min_speed, medium_speed, 1);
      delay(200);
      roboCarHandler.move(0, min_speed, medium_speed, 0);
      break;
    case 0b01000:
    case 0b01100:
      roboCarHandler.move(1, medium_speed, medium_speed, 1);
      delay(200);
      roboCarHandler.move(0, medium_speed, medium_speed, 0);
      break;
    case 0b00100:
    case 0b01110:
      roboCarHandler.move(1, medium_speed, medium_speed, 1);
      delay(200);
      roboCarHandler.move(0, medium_speed, medium_speed, 0);
      break;
    case 0b00010:
    case 0b00110:
      roboCarHandler.move(1, medium_speed, medium_speed, 1);
      delay(200);
      roboCarHandler.move(0, medium_speed, medium_speed, 0);
      break;
    case 0b00111:
      roboCarHandler.move(1, medium_speed, min_speed, 1);
      delay(200);
      roboCarHandler.move(0, medium_speed, min_speed, 0);
      break;
    case 0b00001:
    case 0b00011:
      roboCarHandler.move(1, medium_speed, min_speed, 0);
      delay(200);
      roboCarHandler.move(0, medium_speed, min_speed, 0);
      break;
    default:
      roboCarHandler.stop();
  }
  Serial.println(lineDetector.toText(signals, text));
  delay(50);
}
