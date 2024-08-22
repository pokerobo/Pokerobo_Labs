#include <Arduino.h>

// Motor A connections
#define EN_A    6
#define IN_1    7
#define IN_2    8

// Motor B connections
#define IN_3    5
#define IN_4    4
#define EN_B    3

void move(int8_t leftDirection, int leftSpeed, int rightSpeed, int8_t rightDirection,
    bool reversed=false) {
  uint8_t in1Val = (leftDirection == 1) ? HIGH : LOW;
  uint8_t in2Val = (leftDirection == -1 || leftDirection == 2) ? HIGH : LOW;
  uint8_t in3Val = (rightDirection == 1) ? HIGH : LOW;
  uint8_t in4Val = (rightDirection == -1 || rightDirection == 2) ? HIGH : LOW;

  int enaVal = leftSpeed;
  int enbVal = rightSpeed;

  if (reversed) {
    in1Val = HIGH - in1Val;
    in2Val = HIGH - in2Val;
    in3Val = HIGH - in3Val;
    in4Val = HIGH - in4Val;
    int tmpVal = enaVal;
    enaVal = enbVal;
    enbVal = tmpVal;
  }

  digitalWrite(IN_1, in1Val);
  digitalWrite(IN_2, in2Val);
  digitalWrite(IN_3, in3Val);
  digitalWrite(IN_4, in4Val);

  analogWrite(EN_A, enaVal);
  analogWrite(EN_B, enbVal);
}

void setup() {
  Serial.begin(57600);

  // Moving forward for 1s
  move(1, 255, 255, 1);
  delay(1000);
  // turn forward on right for 100 milliseconds
  move(1, 255, 255, 0);
  delay(150);
  // Moving backward for 1s
  move(-1, 255, 255, -1);
  delay(1000);

  // Moving forward for 1s
  move(1, 255, 255, 1);
  delay(1000);
  // turn backward on left for 100 milliseconds
  move(-1, 255, 255, 0);
  delay(150);
  // Moving backward for 1s
  move(-1, 255, 255, -1);
  delay(1000);
}

void loop() {
}
