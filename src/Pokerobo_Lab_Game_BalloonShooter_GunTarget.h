#ifndef __POKEROBO_LAB_GAME_BALLOON_SHOOTER_GUN_TARGET_H__
#define __POKEROBO_LAB_GAME_BALLOON_SHOOTER_GUN_TARGET_H__

#include "Pokerobo_Lab_Display_Handler.h"
#include "Pokerobo_Lab_Display_Layout.h"

#ifndef SHOOTING_TARGET_MAX_STEP_SPEED
#define SHOOTING_TARGET_MAX_STEP_SPEED        10
#endif//SHOOTING_TARGET_MAX_STEP_SPEED

#ifndef SHOOTING_TARGET_DEADZONE_BOUND
#define SHOOTING_TARGET_DEADZONE_BOUND        30
#endif//SHOOTING_TARGET_DEADZONE_BOUND

struct ShootingTargetLogger {
  virtual void speedOfX_Log(lcd_layout_t layout, int jX, int jY, int rX) {}
  virtual void speedOfY_Log(lcd_layout_t layout, int jX, int jY, int rY) {}
};

struct VerboseShootingTargetLogger: public ShootingTargetLogger {
  void speedOfX_Log(lcd_layout_t layout, int jX, int jY, int rX);
  void speedOfY_Log(lcd_layout_t layout, int jX, int jY, int rY);
};

class ShootingTarget {
  public:
    ShootingTarget(GeometryDisplayHandler* pencil, ShootingTargetLogger* logger=NULL);
    void moveByJoystick(uint16_t x, uint16_t y);
    int8_t speedOfX(uint16_t x, uint16_t y);
    int8_t speedOfY(uint16_t x, uint16_t y);
    int8_t moveX(int8_t deltaX);
    int8_t moveY(int8_t deltaY);
    int8_t getX();
    int8_t getY();
    virtual void draw();
  protected:
    void initialize();
    int adjustX(uint16_t jX);
    int adjustY(uint16_t jY);
    virtual int8_t getStepSpeedMax();
    virtual void drawCross(int8_t x, int8_t y, int8_t d=2, bool straight=true);
    GeometryDisplayHandler* getPencil();
  private:
    int8_t x;
    int8_t y;
    GeometryDisplayHandler* _pencil = NULL;
    ShootingTargetLogger* _logger = NULL;
};

class ShootingTargetInSquare: public ShootingTarget {
  public:
    using ShootingTarget::ShootingTarget;
    void draw();
  protected:
    void drawCross(int8_t x, int8_t y, int8_t d=2, bool straight=true);
};

class ShootingTargetInCircle: public ShootingTargetInSquare {
  public:
    using ShootingTargetInSquare::ShootingTargetInSquare;
    void draw();
};

#endif
