#include <pcf8574.h>

PCF8574 ex0(0x20);

const int pinOuts[5] = { 0, 1, 2, 3, 4 };
int irVals[5] = { 0 };

void setup() {
  delay(200);
  Serial.begin(57600);
  for(int i=0; i<5; i++) {
    pinMode(ex0, pinOuts[i], INPUT);
  }
}

void loop() {
  for(int i=0; i<5; i++) {
    irVals[i] = digitalRead(ex0, pinOuts[i]);
  }
  delay(200);

  Serial.print("Digital Reading=");
  for(int i=0; i<5; i++) {
    Serial.print(irVals[i]);
  }
  Serial.println();
  delay(200);
}
