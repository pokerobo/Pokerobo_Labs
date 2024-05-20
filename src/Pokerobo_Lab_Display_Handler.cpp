#include <U8g2lib.h>
#include "Pokerobo_Lab_Display_Handler.h"

void GeometryDisplayHandler::firstPage() {
  U8G2 *_u8g2 = (U8G2*)_u8g2Ref;
  _u8g2->firstPage();
}

uint8_t GeometryDisplayHandler::nextPage() {
  U8G2 *_u8g2 = (U8G2*)_u8g2Ref;
  return _u8g2->nextPage();
}

u8g2_uint_t GeometryDisplayHandler::getDisplayHeight(void) {
  U8G2* u8g2 = (U8G2*)(_u8g2Ref);
  return u8g2->getDisplayHeight();
}

u8g2_uint_t GeometryDisplayHandler::getDisplayWidth(void) {
  U8G2* u8g2 = (U8G2*)(_u8g2Ref);
  return u8g2->getDisplayWidth();
}

u8g2_uint_t GeometryDisplayHandler::getMaxCharHeight() {
  U8G2* u8g2 = (U8G2*)(_u8g2Ref);
  return u8g2->getMaxCharHeight();
}

u8g2_uint_t GeometryDisplayHandler::getMaxCharWidth() {
  U8G2* u8g2 = (U8G2*)(_u8g2Ref);
  return u8g2->getMaxCharWidth();
}

void GeometryDisplayHandler::setFont(const uint8_t *font) {
  U8G2* u8g2 = (U8G2*)(_u8g2Ref);
  u8g2->setFont(font);
}

void GeometryDisplayHandler::drawBox(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h) {
  U8G2* u8g2 = (U8G2*)(_u8g2Ref);
  u8g2->drawBox(x, y, w, h);
}

void GeometryDisplayHandler::drawButtonUTF8(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t flags, u8g2_uint_t w, u8g2_uint_t padding_h, u8g2_uint_t padding_v, const char *text) {
  U8G2* u8g2 = (U8G2*)(_u8g2Ref);
  u8g2->drawButtonUTF8(x, y, flags, w, padding_h, padding_v, text);
}

void GeometryDisplayHandler::drawFrame(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h) {
  U8G2* u8g2 = (U8G2*)(_u8g2Ref);
  u8g2->drawFrame(x, y, w, h);
}

void GeometryDisplayHandler::drawCircle(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad) {
  this->drawCircle(x0, y0, rad, U8G2_DRAW_ALL);
}

void GeometryDisplayHandler::drawCircle(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad, uint8_t opt) {
  U8G2* u8g2 = (U8G2*)(_u8g2Ref);
  u8g2->drawCircle(x0, y0, rad, opt);
}

void GeometryDisplayHandler::drawDisc(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad) {
  this->drawDisc(x0, y0, rad, U8G2_DRAW_ALL);
}

void GeometryDisplayHandler::drawDisc(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad, uint8_t opt) {
  U8G2* u8g2 = (U8G2*)(_u8g2Ref);
  u8g2->drawDisc(x0, y0, rad, opt);
}

void GeometryDisplayHandler::drawLine(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t x1, u8g2_uint_t y1) {
  U8G2* u8g2 = (U8G2*)(_u8g2Ref);
  u8g2->drawLine(x0, y0, x1, y1);
}

void GeometryDisplayHandler::drawHLine(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w) {
  U8G2* u8g2 = (U8G2*)(_u8g2Ref);
  u8g2->drawHLine(x, y, w);
}

void GeometryDisplayHandler::drawVLine(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t h) {
  U8G2* u8g2 = (U8G2*)(_u8g2Ref);
  u8g2->drawHLine(x, y, h);
}

void GeometryDisplayHandler::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
  U8G2* u8g2 = (U8G2*)(_u8g2Ref);
  u8g2->drawTriangle(x0, y0, x1, y1, x2, y2);
}

void GeometryDisplayHandler::drawTriangleOutline(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
  U8G2* u8g2 = (U8G2*)(_u8g2Ref);
  u8g2->drawLine(x0, y0, x1, y1);
  u8g2->drawLine(x1, y1, x2, y2);
  u8g2->drawLine(x2, y2, x0, y0);
}

void GeometryDisplayHandler::drawPixel(u8g2_uint_t x, u8g2_uint_t y) {
  U8G2* u8g2 = (U8G2*)(_u8g2Ref);
  u8g2->drawPixel(x, y);
}

uint16_t GeometryDisplayHandler::drawStr(u8g2_uint_t x, u8g2_uint_t y, const char* text) {
  U8G2* u8g2 = (U8G2*)(_u8g2Ref);
  return u8g2->drawStr(x, y, text);
}

void GeometryDisplayHandler::clear() {
  U8G2 *_u8g2 = (U8G2*)_u8g2Ref;
  _u8g2->clear();
}
