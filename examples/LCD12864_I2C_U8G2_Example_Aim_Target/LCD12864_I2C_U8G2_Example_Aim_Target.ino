#include <U8g2lib.h>
#include <Pokerobo_RCB_master.h>

U8G2_ST7567_ENH_DG128064I_1_HW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

class AimTarget {
  public:
    AimTarget(byte type);
    void render();
    int8_t speedOfX(uint16_t x);
    int8_t speedOfY(uint16_t y);
    int8_t moveX(int8_t joyX);
    int8_t moveY(int8_t joyY);
  private:
    void drawPlus(int8_t x, int8_t y, int8_t d);
    byte _type;
    int8_t x;
    int8_t y;
};

AimTarget::AimTarget(byte type=2) {
  _type = type;
  x = 63;
  y = 31;
}

void AimTarget::render() {
  switch(_type) {
    case 0:
      u8g2.drawPixel(x, y);
      break;
    case 1:
      drawPlus(x, y, 4);
      u8g2.drawFrame(x-3, y-3, 7, 7);
      break;
    case 2:
      drawPlus(x, y, 5);
      u8g2.drawCircle(x, y, 4);
      break;
    default:
      drawPlus(x, y, 3);
  }
}

void AimTarget::drawPlus(int8_t x, int8_t y, int8_t d) {
  int8_t x1 = (x-d >= 0) ? x-d : 0;
  int8_t x2 = (x+d <= 127) ? x+d : 127;
  int8_t y1 = (y-d >= 0) ? y-d : 0;
  int8_t y2 = (y+d <= 63) ? y+d : 63;
  u8g2.drawLine(x1, y, x2, y);
  u8g2.drawLine(x, y1, x, y2);
}

int8_t AimTarget::speedOfX(uint16_t x) {
  int jX = -512 + x;

  Serial.print("jX: "), Serial.print(jX);
  Serial.print(" -> ");

  if (-30 < jX && jX < 30) {
    jX = 0;
  }

  int rX = map(jX, -512, 512, 5, -5);

  Serial.print("rX: "), Serial.print(rX);
  Serial.println();

  return rX;
}

int8_t AimTarget::speedOfY(uint16_t y) {
  int jY = -512 + y;

  Serial.print("jY: "), Serial.print(jY);
  Serial.print(" -> ");

  if (-30 < jY && jY < 30) {
    jY = 0;
  }

  int rY = map(jY, -512, 512, -5, 5);

  Serial.print("rY: "), Serial.print(rY);
  Serial.println();

  return rY;
}

int8_t AimTarget::moveX(int8_t dX) {
  int8_t oX = x;
  if (dX < 0 && x < -dX) {
    x = 0;
  } else if (dX > 0 && x > 127 - dX) {
    x = 127;
  } else {
    x = x + dX;
  }
  return x - oX;
}

int8_t AimTarget::moveY(int8_t dY) {
  int8_t oY = y;
  if (y < -dY) {
    y = 0;
  } else if (y > 63 - dY) {
    y = 63;
  } else {
    y = y + dY;
  }
  return y - oY;
}

JoystickHandler joystickHandler;
AimTarget target(1);

void setup() {
  u8g2.setI2CAddress(0x3F * 2); 
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  Serial.begin(57600);

  joystickHandler.begin();
}

void loop() {
  JoystickAction action = joystickHandler.input();

  int8_t rX = target.speedOfX(action.getX());
  int8_t rY = target.speedOfY(action.getY());

  target.moveX(rX);
  target.moveY(rY);

  u8g2.firstPage();
  do {
    target.render();
  } while (u8g2.nextPage());

  delay(5);
}
