#include "Pokerobo_Lib_Aim_Target.h"
#include "Pokerobo_Lib_Display_Helper.h"

AimTarget::AimTarget(void* u8g2Ref, lcd_layout_t layout, byte type) {
  _u8g2Ref = u8g2Ref;
  _layout = layout;
  _type = type;
  switch (_layout) {
    case LCD_LAYOUT_R0:
    case LCD_LAYOUT_R2:
      x = 63;
      y = 31;
      _maxX = 127;
      _maxY = 63;
      break;
    case LCD_LAYOUT_R1:
    case LCD_LAYOUT_R3:
      x = 31;
      y = 63;
      _maxX = 63;
      _maxY = 127;
      break;
  }
}

void AimTarget::render() {
  U8G2* u8g2 = (U8G2*)_u8g2Ref;
  switch(_type) {
    case 0:
      u8g2->drawPixel(x, y);
      break;
    case 1:
      drawPlus(x, y, 4);
      u8g2->drawFrame(x-3, y-3, 7, 7);
      break;
    case 2:
      drawPlus(x, y, 5);
      u8g2->drawCircle(x, y, 4);
      break;
    default:
      drawPlus(x, y, 3);
  }
}

void AimTarget::drawPlus(int8_t x, int8_t y, int8_t d) {
  int8_t x1 = (x-d >= 0) ? x-d : 0;
  int8_t x2 = (x+d <= _maxX) ? x+d : _maxX;
  int8_t y1 = (y-d >= 0) ? y-d : 0;
  int8_t y2 = (y+d <= _maxY) ? y+d : _maxY;
  U8G2* u8g2 = (U8G2*)_u8g2Ref;
  u8g2->drawLine(x1, y, x2, y);
  u8g2->drawLine(x, y1, x, y2);
}

int8_t AimTarget::speedOfX(uint16_t x, uint16_t y) {
  int jX = -512 + x;
  if (-30 < jX && jX < 30) {
    jX = 0;
  }

  int jY = -512 + y;
  if (-30 < jY && jY < 30) {
    jY = 0;
  }

  int rX = 0;
  switch (_layout) {
    case LCD_LAYOUT_R0:
    case LCD_LAYOUT_R2:
      Serial.print("jX: "), Serial.print(jX), Serial.print(" -> ");
      rX = map(jX, -512, 512, -10, 10);
      break;
    case LCD_LAYOUT_R1:
      Serial.print("jY: "), Serial.print(jY), Serial.print(" -> ");
      rX = map(jY, -512, 512, -10, 10);
      break;
    case LCD_LAYOUT_R3:
      Serial.print("jY: "), Serial.print(jY), Serial.print(" -> ");
      rX = map(jY, -512, 512, 10, -10);
      break;
  }
  Serial.print("rX: "), Serial.print(rX), Serial.println();

  return rX;
}

int8_t AimTarget::speedOfY(uint16_t x, uint16_t y) {
  int jX = -512 + x;
  if (-30 < jX && jX < 30) {
    jX = 0;
  }

  int jY = -512 + y;
  if (-30 < jY && jY < 30) {
    jY = 0;
  }

  int rY = 0;
  switch (_layout) {
    case LCD_LAYOUT_R0:
    case LCD_LAYOUT_R2:
      Serial.print("jY: "), Serial.print(jY), Serial.print(" -> ");
      rY = map(jY, -512, 512, 10, -10);
      break;
    case LCD_LAYOUT_R1:
      Serial.print("jX: "), Serial.print(jX), Serial.print(" -> ");
      rY = map(jX, -512, 512, -10, 10);
      break;
    case LCD_LAYOUT_R3:
      Serial.print("jX: "), Serial.print(jX), Serial.print(" -> ");
      rY = map(jX, -512, 512, 10, -10);
      break;
  }
  Serial.print("rY: "), Serial.print(rY), Serial.println();

  return rY;
}

int8_t AimTarget::moveX(int8_t dX) {
  int8_t oX = x;
  if (dX < 0 && x < -dX) {
    x = 0;
  } else if (dX > 0 && x > _maxX - dX) {
    x = _maxX;
  } else {
    x = x + dX;
  }
  return x - oX;
}

int8_t AimTarget::moveY(int8_t dY) {
  int8_t oY = y;
  if (y < -dY) {
    y = 0;
  } else if (y > _maxY - dY) {
    y = _maxY;
  } else {
    y = y + dY;
  }
  return y - oY;
}
