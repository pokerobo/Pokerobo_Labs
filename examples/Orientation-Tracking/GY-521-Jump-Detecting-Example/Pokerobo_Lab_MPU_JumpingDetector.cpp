#include "Pokerobo_Lab_MPU_JumpingDetector.h"

void JumpingListener::onJumpingBegin() {
  Serial.println("Jumping begin");
}

void JumpingListener::onJumpingEnd() {
  Serial.println("Jumping end");
}

void JumpingListener::onSquattingBegin() {
  Serial.println("Squatting begin");
}

void JumpingListener::onSquattingEnd() {
  Serial.println("Squatting end");
}


void JumpingDetector::update(int16_t ax, int16_t ay, int16_t az) {
  if (_renderer != NULL) {
    _renderer->update(az);
  }

  // Phát hiện nhảy lên
  // Gia tốc giảm mạnh khi người nhảy lên (cảm biến sẽ cho giá trị âm lớn khi người rời khỏi mặt đất)
  if (isIdle() && isWaitingTimeOver() && az > 32000) {
    logSwitchState_(MOTION_STATE_JUMPING_UP, az);
    if (_listener != NULL) {
      _listener->onJumpingBegin();
    }
    _state = MOTION_STATE_JUMPING_UP;
    lastMillis = millis();  // Ghi lại thời gian nhảy bắt đầu
  }

  if (isIdle() && isWaitingTimeOver() && az < 5000) {
    logSwitchState_(MOTION_STATE_SQUATTING_DOWN, az);
    if (_listener != NULL) {
      _listener->onSquattingBegin();
    }
    _state = MOTION_STATE_SQUATTING_DOWN;
    lastMillis = millis();  // Ghi lại thời gian nhảy bắt đầu
  }

  // Kiểm tra khi gia tốc theo Z tăng lên (người tiếp đất)
  if (_state == MOTION_STATE_JUMPING_UP && az < 22000) {
    logSwitchState_(MOTION_STATE_JUMPING_DOWN, az);
    _state = MOTION_STATE_JUMPING_DOWN;
  }

  if (_state == MOTION_STATE_SQUATTING_DOWN && az > 16000) {
    logSwitchState_(MOTION_STATE_SQUATTING_UP, az);
    _state = MOTION_STATE_SQUATTING_UP;
  }

  if (_state == MOTION_STATE_JUMPING_DOWN && az < 18000) {
    if (_listener != NULL) {
      _listener->onJumpingEnd();
    }
    logSwitchState_(MOTION_STATE_IDLE, az);
    _state = MOTION_STATE_IDLE;
    finishMillis = millis();
  }

  if (_state == MOTION_STATE_SQUATTING_UP && az > 25000) {
    if (_listener != NULL) {
      _listener->onSquattingEnd();
    }
    logSwitchState_(MOTION_STATE_IDLE, az);
    _state = MOTION_STATE_IDLE;
    finishMillis = millis();
  }

  if (isJumping() && exceedThresholdTime()) {
    logSwitchState_(MOTION_STATE_IDLE, az, true);
    _state = MOTION_STATE_IDLE;
    finishMillis = millis();
    lastMillis = millis();
  }

  if (isSquatting() && exceedThresholdTime()) {
    logSwitchState_(MOTION_STATE_IDLE, az, true);
    _state = MOTION_STATE_IDLE;
    finishMillis = millis();
    lastMillis = millis();
  }
}


void JumpingDetector::render() {
  _pen->firstPage();
  do {
    if (_renderer != NULL) {
      _renderer->draw();
    }
    showinfo();
  } while (_pen->nextPage());
}

void JumpingDetector::showinfo() {
  switch(_state) {
    case MOTION_STATE_IDLE:
      _pen->drawStr(0, 32, "Stand still");
      break;
    case MOTION_STATE_JUMPING_UP:
      _pen->drawStr(0, 32, "Dang nhay len");
      break;
    case MOTION_STATE_JUMPING_DOWN:
      _pen->drawStr(0, 32, "Dang roi xuong");
      break;
    case MOTION_STATE_SQUATTING_DOWN:
      _pen->drawStr(0, 32, "Dang thup xuong");
      break;
    case MOTION_STATE_SQUATTING_UP:
      _pen->drawStr(0, 32, "Dang dung len");
      break;
  }
}

bool JumpingDetector::exceedThresholdTime() {
  return millis() - lastMillis > 2*actionThresholdTime;
}

bool JumpingDetector::isWaitingTimeOver() {
  return millis() - finishMillis > 700;
}

bool JumpingDetector::isIdle() {
  return _state == MOTION_STATE_IDLE;
}

bool JumpingDetector::isJumping() {
  return _state == MOTION_STATE_JUMPING_UP || _state == MOTION_STATE_JUMPING_DOWN;
}

bool JumpingDetector::isSquatting() {
  return _state == MOTION_STATE_SQUATTING_UP || _state == MOTION_STATE_SQUATTING_DOWN;
}

motion_state_t JumpingDetector::getState() {
  return _state;
}

GeometryDisplayHandler* JumpingDetector::getDisplayHandler() {
  return _pen;
}

void JumpingDetector::logSwitchState_(motion_state_t next_state, int16_t az, bool auto_change) {
}
