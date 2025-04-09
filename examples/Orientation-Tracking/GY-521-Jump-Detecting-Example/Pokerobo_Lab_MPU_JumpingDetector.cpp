#include "Pokerobo_Lab_MPU_JumpingDetector.h"

JumpingListener::JumpingListener(bool serialLog) {
  _serialLog = serialLog;
}

void JumpingListener::onJumpingBegin() {
  if (_serialLog) {
    Serial.println("Jumping begin");
  }
}

void JumpingListener::onJumpingEnd() {
  if (_serialLog) {
    Serial.println("Jumping end");
  }
}

void JumpingListener::onSquattingBegin() {
  if (_serialLog) {
    Serial.println("Squatting begin");
  }
}

void JumpingListener::onSquattingEnd() {
  if (_serialLog) {
    Serial.println("Squatting end");
  }
}

//-------------------------------------------------------------------------------------------------

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

void JumpingDetector::initialize() {
}

void JumpingDetector::showinfo() {
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

//-------------------------------------------------------------------------------------------------

void JumpingDetectorSerialLog::logSwitchState_(motion_state_t next_state, int16_t az, bool auto_change) {
  if (auto_change) {
    Serial.print(" auto [");
  } else {
    Serial.print(" [");
  }
  Serial.print(stringify(getState()));
  Serial.print("]->[");
  Serial.print(stringify(next_state));
  Serial.print("] with az: ");
  Serial.println(az);
  if (next_state == MOTION_STATE_IDLE) {
    Serial.println();
  }
}

char* JumpingDetectorSerialLog::stringify(motion_state_t state) {
  switch(state) {
    case MOTION_STATE_IDLE:
      return "idle";
    case MOTION_STATE_JUMPING_UP:
      return "jumping_up";
    case MOTION_STATE_JUMPING_DOWN:
      return "jumping_down";
    case MOTION_STATE_SQUATTING_DOWN:
      return "squatting_down";
    case MOTION_STATE_SQUATTING_UP:
      return "squatting_up";
  }
}

//-------------------------------------------------------------------------------------------------

void JumpingDetectorScreenLog::initialize() {
  _charHeight = getDisplayHandler()->getMaxCharHeight();
}

void JumpingDetectorScreenLog::showinfo() {
  for(int i=0; i<JUMPING_LOG_TOTAL; i++) {
    int j = i + _line_head;
    while (j >= JUMPING_LOG_TOTAL) {
      j -= JUMPING_LOG_TOTAL;
    }
    u8g2_uint_t x = 0;
    u8g2_uint_t y = _charHeight * (i + 1);
    getDisplayHandler()->drawStr(x, y, _lines[j]);
  }
}

void JumpingDetectorScreenLog::logSwitchState_(motion_state_t next_state, int16_t az, bool auto_change) {
  lineFeed_();
  sprintf(_lines[_line_tail], "[%s->%s]% 5d", stringify(getState()), stringify(next_state), az);
  if (next_state == MOTION_STATE_IDLE) {
    lineFeed_();
    _lines[_line_tail][0] = '\0';
  }
}

void JumpingDetectorScreenLog::lineFeed_() {
  if (_line_tail < (JUMPING_LOG_TOTAL - 1)) {
    _line_tail += 1;
  } else {
    _line_tail = 0;
  }
  _line_head = _line_tail + 1;
  while (_line_head >= JUMPING_LOG_TOTAL) {
    _line_head -= JUMPING_LOG_TOTAL;
  }
}

char* JumpingDetectorScreenLog::stringify(motion_state_t state) {
  switch(state) {
    case MOTION_STATE_IDLE:
      return "ID";
    case MOTION_STATE_JUMPING_UP:
      return "JU";
    case MOTION_STATE_JUMPING_DOWN:
      return "JD";
    case MOTION_STATE_SQUATTING_DOWN:
      return "SD";
    case MOTION_STATE_SQUATTING_UP:
      return "SU";
  }
}

//-------------------------------------------------------------------------------------------------

JumpingDemoProgram::JumpingDemoProgram(JumpingDetector *detector, char *title): ProgramSticker(title) {
  _detector = detector;
}

int JumpingDemoProgram::begin() {
  return 0;
}

int JumpingDemoProgram::check(void* action, void* command) {
  _detector->render();
  return 0;
}

int JumpingDemoProgram::close() {
  return 0;
}
