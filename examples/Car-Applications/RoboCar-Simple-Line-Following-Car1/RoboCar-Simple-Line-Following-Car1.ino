#include "Pokerobo_Car.h"

const int max_speed = 180;

DisplayAdapter displayAdapter;
LineDetector5Channels lineDetector;

RoboCarHandler roboCarHandler;
MovingResolver movingResolver;

char text[9] = { 0 };

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
    case 0b11100:
    case 0b01110:
    case 0b00111:
    case 0b00011:
    case 0b00001:
      roboCarHandler.move(1, max_speed, max_speed, 1);
      break;
    case 0b11111:
    case 0b00000:
      roboCarHandler.stop();
      break;
  }
  Serial.println(lineDetector.toText(signals, text));
  delay(200);
}
