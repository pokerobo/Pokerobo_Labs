#include "Motor_Speed_Calculator.h"

MotorSpeedCalculator msc;

void setup () {
  Serial.begin(57600);
  msc.begin();
}

void loop () {
  delay(1000);

  Serial.print("Speed of Motor A: ");
  Serial.print(msc.speedOfMotorA);
  Serial.print(" RPM");

  Serial.print(" - ");

  Serial.print("Speed of Motor B: ");
  Serial.print(msc.speedOfMotorB);
  Serial.println(" RPM");
}
