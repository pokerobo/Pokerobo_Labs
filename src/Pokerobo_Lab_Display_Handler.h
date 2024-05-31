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

extern const uint8_t* text_font_title_bold;
extern const uint8_t* text_font_body_normal;

#ifndef U8G2_H //~u8g2.h

/* u8g2_button.c */

/* border width */
#define U8G2_BTN_BW_POS 0
#define U8G2_BTN_BW_MASK 7
#define U8G2_BTN_BW0 0x00
#define U8G2_BTN_BW1 0x01
#define U8G2_BTN_BW2 0x02
#define U8G2_BTN_BW3 0x03

/* enable shadow and define gap to button */
#define U8G2_BTN_SHADOW_POS 3
#define U8G2_BTN_SHADOW_MASK 0x18
#define U8G2_BTN_SHADOW0 0x08
#define U8G2_BTN_SHADOW1 0x10
#define U8G2_BTN_SHADOW2 0x18

/* text is displayed inverted */
#define U8G2_BTN_INV 0x20

/* horizontal center */
#define U8G2_BTN_HCENTER 0x40

/* second one pixel frame */
#define U8G2_BTN_XFRAME 0x80


/* u8g2_circle.c */

#define U8G2_DRAW_UPPER_RIGHT  0x01
#define U8G2_DRAW_UPPER_LEFT   0x02
#define U8G2_DRAW_LOWER_LEFT   0x04
#define U8G2_DRAW_LOWER_RIGHT  0x08
#define U8G2_DRAW_ALL (U8G2_DRAW_UPPER_RIGHT|U8G2_DRAW_UPPER_LEFT|U8G2_DRAW_LOWER_RIGHT|U8G2_DRAW_LOWER_LEFT)

#endif//U8G2_H

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
    void setDrawColor(uint8_t color_index);
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
