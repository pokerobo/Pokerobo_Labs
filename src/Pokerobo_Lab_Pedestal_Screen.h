#ifndef __POKEROBO_LAB_PEDESTAL_SCREEN_H__
#define __POKEROBO_LAB_PEDESTAL_SCREEN_H__

#include <Pokerobo_Arm.h>
#include <Pokerobo_RCB.h>
#include "Pokerobo_Lab_Display_Handler.h"

class PedestalDisplayHandler: public GeometryDisplayHandler {
  public:
    using GeometryDisplayHandler::GeometryDisplayHandler;
    void render(JoystickAction *action, PedestalState *state);
  protected:
    virtual void prepareDisplay(JoystickAction *action, PedestalState *state);
    virtual void renderInternal(JoystickAction *action, PedestalState *state);
  private:
    char _title[16] = "Pedestals";
    char _lines[4][16] = {{0}, {0}, {0}, {0}};
};

struct CoordinatePoint {
  int x;
  int y;
};

//-------------------------------------------------------------------------------------------------

class AdvancedDisplayHandler: public PedestalDisplayHandler {
  public:
    using PedestalDisplayHandler::PedestalDisplayHandler;
};

//-------------------------------------------------------------------------------------------------

class Pedestal2DisplayHandler: public AdvancedDisplayHandler {
  public:
    using AdvancedDisplayHandler::AdvancedDisplayHandler;
  protected:
    virtual void prepareDisplay(JoystickAction *action, PedestalState *state);
    virtual void renderInternal(JoystickAction *action, PedestalState *state);
  private:
    CoordinatePoint getHorizontalCenterOf_(uint8_t i);
    CoordinatePoint getHorizontalPointOf_(uint8_t i, PedestalState *state, CoordinatePoint *center, bool isBound=false);
    CoordinatePoint getVerticalCenterOf_(uint8_t i);
    CoordinatePoint getVerticalPointOf_(uint8_t i, PedestalState *state, CoordinatePoint *center, bool isBound=false);
    uint8_t _top = 0;
    uint8_t _left = 64;
    uint8_t _radius = 10;
    uint8_t _leftPad = 5;
    uint8_t _horizontalPad = 5;
    uint8_t _verticalPad = 4;
    uint8_t _topPad = 5;
};

//-------------------------------------------------------------------------------------------------

class Pedestal3DisplayHandler: public AdvancedDisplayHandler {
  public:
    using AdvancedDisplayHandler::AdvancedDisplayHandler;
  protected:
    virtual void prepareDisplay(JoystickAction *action, PedestalState *state);
    virtual void renderInternal(JoystickAction *action, PedestalState *state);
  private:
    CoordinatePoint getHorizontalCenterOf_(uint8_t i);
    CoordinatePoint getMinPointOf_(uint8_t i, CoordinatePoint *center, PedestalState *state);
    CoordinatePoint getNormalPointOf_(uint8_t i, CoordinatePoint *center, PedestalState *state);
    CoordinatePoint getMaxPointOf_(uint8_t i, CoordinatePoint *center, PedestalState *state);
    CoordinatePoint calculatePointWithDistance_(CoordinatePoint *c, int angle, uint8_t distance);
    uint8_t _top = 0;
    uint8_t _topPad = 16;
    uint8_t _left = 0;
    uint8_t _leftPad = 3;
    uint8_t _radius = 14;
    uint8_t _horizontalPad = 3;
    uint8_t _verticalPad = 0;
};

#endif
