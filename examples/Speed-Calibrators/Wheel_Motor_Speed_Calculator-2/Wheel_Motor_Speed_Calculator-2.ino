#include "Motor_Speed_Calculator.h"

void setup () {
  Serial.begin(57600);
  MotorSpeedCalculator::start();
}

void loop () {
  delay(1000);

  Serial.print("Speed of Motor A: ");
  Serial.print(MotorSpeedCalculator::speedOfMotorA);
  Serial.print(" RPM");

  Serial.print(" - ");

  Serial.print("Speed of Motor B: ");
  Serial.print(MotorSpeedCalculator::speedOfMotorB);
  Serial.println(" RPM");
}
