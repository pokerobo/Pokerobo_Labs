#include <Servo.h>
#include <Pokerobo_RCB.h>
#include "Pokerobo_Lab_Display_Handler.h"

GeometryDisplayHandler displayHandler;

char positionStr[22] = {0};
char delayTimeStr[22] = {0};

void displayServoPosition(uint8_t position, int delayTime=1000) {
  displayHandler.firstPage();
  displayHandler.setFont(text_font_body_normal);
  uint8_t _maxCharHeight = displayHandler.getMaxCharHeight();
  uint8_t _maxCharWidth = displayHandler.getMaxCharWidth();
  sprintf(positionStr, "Servo position: %3d", position);
  sprintf(delayTimeStr, "Delay time: %d ms", delayTime);
  do {
    displayHandler.drawStr(64 - strlen(positionStr)*_maxCharWidth / 2, 32, positionStr);
    displayHandler.drawStr(64 - strlen(delayTimeStr)*_maxCharWidth / 2, 32 + _maxCharHeight, delayTimeStr);
  } while (displayHandler.nextPage());
}

Servo servo;

void setup() {
  Serial.begin(57600);
  displayHandler.begin();
  servo.attach(2);
  servo.write(0);
  delay(1000);
}
 
void loop() {
  servo.write(180);
  displayServoPosition(180, 1000);
  delay(1000);

  servo.write(90);
  displayServoPosition(90, 5000);
  delay(5000);

  servo.write(0);
  displayServoPosition(0, 5000);
  delay(5000);
}
