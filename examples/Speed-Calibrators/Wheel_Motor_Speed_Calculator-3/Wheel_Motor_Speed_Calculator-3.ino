#include "Pokerobo_Car_improvement.h"

MotorSpeedCalculator c;

void setup () {
  Serial.begin(57600);
  c.start();
}

void loop () {
  delay(1000);

  Serial.print("Speed of Motor A: ");
  Serial.print(c.speedOfMotorA);
  Serial.print(" RPM");

  Serial.print(" - ");

  Serial.print("Speed of Motor B: ");
  Serial.print(c.speedOfMotorB);
  Serial.println(" RPM");
}
