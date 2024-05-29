#include <U8g2lib.h>
#include "Pokerobo_Lab_Display_Handler.h"

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
  U8G2* u8g2 = (U8G2*)getU8g2Ref();
  return u8g2->getDisplayHeight();
}

u8g2_uint_t GeometryDisplayHandler::getDisplayWidth() {
  U8G2* u8g2 = (U8G2*)getU8g2Ref();
  return u8g2->getDisplayWidth();
}

u8g2_uint_t GeometryDisplayHandler::getMaxCharHeight() {
  U8G2* u8g2 = (U8G2*)getU8g2Ref();
  return u8g2->getMaxCharHeight();
}

u8g2_uint_t GeometryDisplayHandler::getMaxCharWidth() {
  U8G2* u8g2 = (U8G2*)getU8g2Ref();
  return u8g2->getMaxCharWidth();
}

void GeometryDisplayHandler::setFont(const uint8_t *font) {
  U8G2* u8g2 = (U8G2*)getU8g2Ref();
  u8g2->setFont(font);
}

void GeometryDisplayHandler::drawBox(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h) {
  U8G2* u8g2 = (U8G2*)getU8g2Ref();
  u8g2->drawBox(x, y, w, h);
}

void GeometryDisplayHandler::drawButtonUTF8(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t flags, u8g2_uint_t w, u8g2_uint_t padding_h, u8g2_uint_t padding_v, const char *text) {
  U8G2* u8g2 = (U8G2*)getU8g2Ref();
  u8g2->drawButtonUTF8(x, y, flags, w, padding_h, padding_v, text);
}

void GeometryDisplayHandler::drawFrame(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h) {
  U8G2* u8g2 = (U8G2*)getU8g2Ref();
  u8g2->drawFrame(x, y, w, h);
}

void GeometryDisplayHandler::drawCircle(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad) {
  this->drawCircle(x0, y0, rad, U8G2_DRAW_ALL);
}

void GeometryDisplayHandler::drawCircle(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad, uint8_t opt) {
  U8G2* u8g2 = (U8G2*)getU8g2Ref();
  u8g2->drawCircle(x0, y0, rad, opt);
}

void GeometryDisplayHandler::drawDisc(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad) {
  this->drawDisc(x0, y0, rad, U8G2_DRAW_ALL);
}

void GeometryDisplayHandler::drawDisc(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad, uint8_t opt) {
  U8G2* u8g2 = (U8G2*)getU8g2Ref();
  u8g2->drawDisc(x0, y0, rad, opt);
}

void GeometryDisplayHandler::drawLine(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t x1, u8g2_uint_t y1) {
  U8G2* u8g2 = (U8G2*)getU8g2Ref();
  u8g2->drawLine(x0, y0, x1, y1);
}

void GeometryDisplayHandler::drawHLine(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w) {
  U8G2* u8g2 = (U8G2*)getU8g2Ref();
  u8g2->drawHLine(x, y, w);
}

void GeometryDisplayHandler::drawVLine(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t h) {
  U8G2* u8g2 = (U8G2*)getU8g2Ref();
  u8g2->drawHLine(x, y, h);
}

void GeometryDisplayHandler::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
  U8G2* u8g2 = (U8G2*)getU8g2Ref();
  u8g2->drawTriangle(x0, y0, x1, y1, x2, y2);
}

void GeometryDisplayHandler::drawTriangleOutline(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
  U8G2* u8g2 = (U8G2*)getU8g2Ref();
  u8g2->drawLine(x0, y0, x1, y1);
  u8g2->drawLine(x1, y1, x2, y2);
  u8g2->drawLine(x2, y2, x0, y0);
}

void GeometryDisplayHandler::drawPixel(u8g2_uint_t x, u8g2_uint_t y) {
  U8G2* u8g2 = (U8G2*)getU8g2Ref();
  u8g2->drawPixel(x, y);
}

uint16_t GeometryDisplayHandler::drawStr(u8g2_uint_t x, u8g2_uint_t y, const char* text) {
  U8G2* u8g2 = (U8G2*)getU8g2Ref();
  return u8g2->drawStr(x, y, text);
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
  char text[7] = { 0 };
  sprintf(text, "%dx%d", displayWidth, displayHeight);
  this->drawStr((displayWidth - strlen(text)*charWidth)/2, displayHeight/2, text);
}

//-------------------------------------------------------------------------------------------------

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

  char lines[4][16] = { {0}, {0}, {0}, {0} };
  sprintf(lines[0], "C%d: %3d,%2d", 0, x0, y0);
  sprintf(lines[1], "C%d: %3d,%2d", 1, x1, y1);
  sprintf(lines[2], "C%d: %3d,%2d", 2, x2, y2);
  sprintf(lines[3], "C%d: %3d,%2d", 3, x3, y3);

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
