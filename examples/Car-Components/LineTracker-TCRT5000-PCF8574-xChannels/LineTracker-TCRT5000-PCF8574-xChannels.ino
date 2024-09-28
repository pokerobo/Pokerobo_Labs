#include "Pokerobo_Car.h"

LineDetectorXChannels lineDetector(0b00010101);
char text[9] = { 0 };

void setup() {
  Serial.begin(57600);
  lineDetector.begin();
  lineDetector.setBlackLine(false);
}

void loop() {
  uint8_t signals = lineDetector.read();
  Serial.println(lineDetector.toText(signals, text, false));
  delay(500);
}
