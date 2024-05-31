#include <U8g2lib.h>
#include "Pokerobo_Lab_Display_Handler.h"

const uint8_t* text_font_title_bold =  u8g2_font_ncenB10_tr;
const uint8_t* text_font_body_normal = u8g2_font_5x8_tf;

U8G2* toU8G2(void* u8g2Ref) {
  return (U8G2*)u8g2Ref;
}

void* GeometryDisplayHandler::getU8g2Ref() {
  return DisplayHandler::getU8g2Ref();
}

void GeometryDisplayHandler::firstPage() {
  DisplayHandler::firstPage();
}

uint8_t GeometryDisplayHandler::nextPage() {
  return DisplayHandler::nextPage();
}

u8g2_uint_t GeometryDisplayHandler::getDisplayHeight() {
  return toU8G2(getU8g2Ref())->getDisplayHeight();
}

u8g2_uint_t GeometryDisplayHandler::getDisplayWidth() {
  return toU8G2(getU8g2Ref())->getDisplayWidth();
}

u8g2_uint_t GeometryDisplayHandler::getMaxCharHeight() {
  return toU8G2(getU8g2Ref())->getMaxCharHeight();
}

u8g2_uint_t GeometryDisplayHandler::getMaxCharWidth() {
  return toU8G2(getU8g2Ref())->getMaxCharWidth();
}

void GeometryDisplayHandler::setFont(const uint8_t *font) {
  toU8G2(getU8g2Ref())->setFont(font);
}

void GeometryDisplayHandler::setDrawColor(const uint8_t color_index) {
  toU8G2(getU8g2Ref())->setDrawColor(color_index);
}

void GeometryDisplayHandler::drawBox(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h) {
  toU8G2(getU8g2Ref())->drawBox(x, y, w, h);
}

void GeometryDisplayHandler::drawButtonUTF8(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t flags, u8g2_uint_t w, u8g2_uint_t padding_h, u8g2_uint_t padding_v, const char *text) {
  toU8G2(getU8g2Ref())->drawButtonUTF8(x, y, flags, w, padding_h, padding_v, text);
}

void GeometryDisplayHandler::drawFrame(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h) {
  toU8G2(getU8g2Ref())->drawFrame(x, y, w, h);
}

void GeometryDisplayHandler::drawCircle(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad) {
  this->drawCircle(x0, y0, rad, U8G2_DRAW_ALL);
}

void GeometryDisplayHandler::drawCircle(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad, uint8_t opt) {
  toU8G2(getU8g2Ref())->drawCircle(x0, y0, rad, opt);
}

void GeometryDisplayHandler::drawDisc(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad) {
  this->drawDisc(x0, y0, rad, U8G2_DRAW_ALL);
}

void GeometryDisplayHandler::drawDisc(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad, uint8_t opt) {
  toU8G2(getU8g2Ref())->drawDisc(x0, y0, rad, opt);
}

void GeometryDisplayHandler::drawLine(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t x1, u8g2_uint_t y1) {
  toU8G2(getU8g2Ref())->drawLine(x0, y0, x1, y1);
}

void GeometryDisplayHandler::drawHLine(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w) {
  toU8G2(getU8g2Ref())->drawHLine(x, y, w);
}

void GeometryDisplayHandler::drawVLine(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t h) {
  toU8G2(getU8g2Ref())->drawHLine(x, y, h);
}

void GeometryDisplayHandler::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
  toU8G2(getU8g2Ref())->drawTriangle(x0, y0, x1, y1, x2, y2);
}

void GeometryDisplayHandler::drawTriangleOutline(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
  U8G2* u8g2 = (U8G2*)getU8g2Ref();
  u8g2->drawLine(x0, y0, x1, y1);
  u8g2->drawLine(x1, y1, x2, y2);
  u8g2->drawLine(x2, y2, x0, y0);
}

void GeometryDisplayHandler::drawPixel(u8g2_uint_t x, u8g2_uint_t y) {
  toU8G2(getU8g2Ref())->drawPixel(x, y);
}

uint16_t GeometryDisplayHandler::drawStr(u8g2_uint_t x, u8g2_uint_t y, const char* text) {
  return toU8G2(getU8g2Ref())->drawStr(x, y, text);
}

void GeometryDisplayHandler::rotateScreen(bool clockwise=true) {
  if (clockwise) {
    this->setDisplayRotation(this->nextDisplayRotation(this->getDisplayRotation()));
  } else {
    this->setDisplayRotation(this->prevDisplayRotation(this->getDisplayRotation()));
  }
}

void GeometryDisplayHandler::showDisplayInfo() {
  uint16_t charWidth = this->getMaxCharWidth();
  uint16_t charHeight = this->getMaxCharHeight();
  uint16_t displayWidth = this->getDisplayWidth();
  uint16_t displayHeight = this->getDisplayHeight();
  char text[7] = { 0 }; // 6 characters "128x64" and one for '\n'
  sprintf(text, "%dx%d", displayWidth, displayHeight);
  this->drawStr((displayWidth - strlen(text)*charWidth)/2, displayHeight/2, text);
}

//-------------------------------------------------------------------------------------------------

void CornersDisplayHandler::drawPage(uint8_t total, uint8_t number, uint16_t h0, uint16_t v0, uint16_t h1, uint16_t v1) {
  char label[total + 1] = { 0 };
  for(int i=0; i<total; i++) {
    if (i == number) {
      label[i] = '0' + i;
    } else {
      label[i] = '-';
    }
  }
  drawCorners(h0, v0, h1, v1, label);
}

void CornersDisplayHandler::drawCorners(uint16_t h0, uint16_t v0, uint16_t h1, uint16_t v1, const char* label) {
  uint16_t charWidth = this->getMaxCharWidth();
  uint16_t charHeight = this->getMaxCharHeight();
  uint16_t displayWidth = this->getDisplayWidth();
  uint16_t displayHeight = this->getDisplayHeight();

  uint16_t x0 = h0, y0 = v0;
  uint16_t x1 = displayWidth - h1, y1 = v0;
  uint16_t x2 = displayWidth - h1, y2 = displayHeight - v1;
  uint16_t x3 = h0, y3 = displayHeight - v1;

  char lines[4][12] = { {0}, {0}, {0}, {0} };
  sprintf(lines[0], "%s: %3d,%2d", "TL", x0, y0);
  sprintf(lines[1], "%s: %3d,%2d", "TR", x1, y1);
  sprintf(lines[2], "%s: %3d,%2d", "BR", x2, y2);
  sprintf(lines[3], "%s: %3d,%2d", "BL", x3, y3);

  uint16_t textBlockX = displayWidth/2 - 3*charWidth;
  uint16_t textBlockY = displayHeight/2 - 1*(charHeight + 1);

  this->firstPage();
  do {
    if (label != NULL) {
      this->drawStr(displayWidth/2 - charWidth*strlen(label)/2,
        charHeight + 1, label);
    }

    drawCorner(x0, y0);
    drawCorner(x1, y1);
    drawCorner(x2, y2);
    drawCorner(x3, y3);

    for(int i=0; i<4; i++) {
      this->drawStr(displayWidth/2 - charWidth*strlen(lines[i])/2,
          textBlockY + i*(charHeight + 1), lines[i]);
    }
  } while (this->nextPage());
}

void CornersDisplayHandler::drawCorner(uint16_t x, uint16_t y) {
  this->drawPixel(x, y);
  this->drawPixel(x+1, y+1);
  if (y > 0) {
    this->drawPixel(x+1, y-1);
  }
  if (x > 0) {
    this->drawPixel(x-1, y+1);
  }
  if (x > 0 & y > 0) {
    this->drawPixel(x-1, y-1);
  }
}
