#include <Servo.h>
#include <U8g2lib.h>
#include <Pokerobo_RCB_master.h>

const u8g2_cb_t* u8g2_rotation = U8G2_R2;

U8G2_ST7567_ENH_DG128064I_1_HW_I2C u8g2(u8g2_rotation, SCL, SDA, U8X8_PIN_NONE);

char positionStr[22] = {0};
char delayTimeStr[22] = {0};

void displayServoPosition(uint8_t position, int delayTime=1000) {
  u8g2.firstPage();
  u8g2.setFont(u8g2_font_5x8_tf);
  uint8_t _maxCharHeight = u8g2.getMaxCharHeight();
  uint8_t _maxCharWidth = u8g2.getMaxCharWidth();
  sprintf(positionStr, "Servo position: %3d", position);
  sprintf(delayTimeStr, "Delay time: %d ms", delayTime);
  do {
    u8g2.drawStr(64 - strlen(positionStr)*_maxCharWidth / 2, 32, positionStr);
    u8g2.drawStr(64 - strlen(delayTimeStr)*_maxCharWidth / 2, 32 + _maxCharHeight, delayTimeStr);
  } while (u8g2.nextPage());
}

Servo servo;

void setup() {
  u8g2.setI2CAddress(0x3F * 2);
  u8g2.begin();
  Serial.begin(57600);
  servo.attach(8);
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
