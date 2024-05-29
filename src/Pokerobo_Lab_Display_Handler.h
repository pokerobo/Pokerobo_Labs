#ifndef __POKEROBO_LAB_DISPLAY_HANDLER_H__
#define __POKEROBO_LAB_DISPLAY_HANDLER_H__

#include <Pokerobo_RCB.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint16_t u8g2_uint_t;

#ifdef __cplusplus
}
#endif

class GeometryDisplayHandler: public DisplayHandler {
  public:
    using DisplayHandler::DisplayHandler;
    void* getU8g2Ref();
    void firstPage();
    uint8_t nextPage();
    u8g2_uint_t getDisplayHeight();
    u8g2_uint_t getDisplayWidth();
    u8g2_uint_t getMaxCharHeight();
    u8g2_uint_t getMaxCharWidth();
    void setFont(const uint8_t *font);
    void drawBitmap(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t cnt, u8g2_uint_t h, const uint8_t *bitmap);
    void drawBox(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h);
    void drawButtonUTF8(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t flags, u8g2_uint_t width, u8g2_uint_t padding_h, u8g2_uint_t padding_v, const char *text);
    void drawFrame(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h);
    void drawCircle(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad);
    void drawCircle(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad, uint8_t opt);
    void drawDisc(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad);
    void drawDisc(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rad, uint8_t opt);
    void drawEllipse(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rx, u8g2_uint_t ry, uint8_t opt);
    void drawFilledEllipse(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t rx, u8g2_uint_t ry, uint8_t opt);
    void drawLine(u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t x1, u8g2_uint_t y1);
    void drawHLine(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w);
    void drawVLine(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t h);
    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2);
    void drawTriangleOutline(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2);
    void drawPixel(u8g2_uint_t x, u8g2_uint_t y);
    uint16_t drawStr(u8g2_uint_t x, u8g2_uint_t y, const char* text);
    void rotateScreen(bool clockwise=true);
    void showDisplayInfo();
};

class CornersDisplayHandler: public GeometryDisplayHandler {
  public:
    void drawPage(uint8_t total, uint8_t number, uint16_t h0, uint16_t v0, uint16_t h1, uint16_t v1);
    void drawCorners(uint16_t h0, uint16_t v0, uint16_t h1, uint16_t v1, const char* label=NULL);
  protected:
    virtual void drawCorner(uint16_t x, uint16_t y);
};

#endif
