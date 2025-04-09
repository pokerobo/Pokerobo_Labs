#include "Pokerobo_Lab_MPU_AcceGyroRenderer.h"

AcceGyroRenderer::AcceGyroRenderer(GeometryDisplayHandler* pen) {
  setDisplayHandler(pen);
  initialize();
}

void AcceGyroRenderer::setDisplayHandler(GeometryDisplayHandler* pen) {
  _pen = pen;
  if (_pen != NULL) {
    _charWidth = _pen->getMaxCharWidth();
  }
}

void AcceGyroRenderer::initialize() {
  int2str_(_maxAccStr, _maxAcc);
  int2str_(_minAccStr, _minAcc);
}

bool AcceGyroRenderer::update(int16_t value) {
  bool _changed = false;

  _value = value;
  int2str_(_valueStr, _value);

  if (_minAcc > _value) {
    _minAcc = _value;
    int2str_(_minAccStr, _minAcc);
    _changed = true;
  }

  if (_maxAcc < _value) {
    _maxAcc = _value;
    int2str_(_maxAccStr, _maxAcc);
    _changed = true;
  }

  return _changed;
}

void AcceGyroRenderer::render() {
  if (_pen == NULL) return;
  _pen->firstPage();
  do {
    draw();
  } while (_pen->nextPage());
}

void AcceGyroRenderer::draw() {
  _pen->drawLine(127 - 6, 3, 127 - 6, 64 - 3);
  _pen->drawStr(127 - 6 - 6*_charWidth,  6, _maxAccStr);
  _pen->drawStr(127 - 6 - 6*_charWidth, 63, _minAccStr);

  int8_t pos = valueToPoint(_value);
  _pen->drawTriangle(127 - 5, pos, 127, pos - 3, 127, pos + 3);
  _pen->drawStr(127 - 6 - 6*_charWidth, pos + 3, _valueStr);
}

char* AcceGyroRenderer::int2str_(char* buffer, int16_t value) {
  sprintf(buffer, "% 5d", value);
  return buffer;
}

int8_t AcceGyroRenderer::valueToPoint(int16_t value) {
  return map(value, _minAcc, _maxAcc, 3, 64 - 3);
}

int16_t AcceGyroRenderer::getValue() {
  return _value;
}

GeometryDisplayHandler* AcceGyroRenderer::getDisplayHandler() {
  return _pen;
}

//-------------------------------------------------------------------------------------------------

bool AcceGyroDiagram::update(int16_t value) {
  bool _changed = AcceGyroRenderer::update(value);

  if (_sample_tail < (ACCE_DIAGRAM_SIZE - 1)) {
    _sample_tail++;
  } else {
    _sample_tail = 0;
  }

  _samples[_sample_tail] = getValue();

  _sample_min = _sample_tail;
  _sample_max = _sample_tail;

  _sample_head = _sample_tail - 1;
  while (_sample_head < 0) {
    _sample_head += ACCE_DIAGRAM_SIZE;
  }

  for(int j=0; j<ACCE_DIAGRAM_SIZE; j++) {
    if (_samples[j] < _samples[_sample_min]) {
      _sample_min = j;
    }
    if (_samples[j] > _samples[_sample_max]) {
      _sample_max = j;
    }
  }

  for(int j=0; j<ACCE_DIAGRAM_SIZE; j++) {
    points[j] = map(_samples[j], _samples[_sample_min], _samples[_sample_max], 3, 64 - 3);
  }
}

void AcceGyroDiagram::draw() {
  AcceGyroRenderer::draw();

  for(int i=0; i<ACCE_DIAGRAM_SIZE; i++) {
    int j = i + _sample_head;
    if (j >= ACCE_DIAGRAM_SIZE) {
      j -= ACCE_DIAGRAM_SIZE;
    }
    getDisplayHandler()->drawPixel(i, points[j]);
  }
}

//-------------------------------------------------------------------------------------------------

int AcceGyroProgram::begin() {
  return 0;
}

int AcceGyroProgram::check(void* action, void* command) {
  _monitor->render();
  return 0;
}

int AcceGyroProgram::close() {
  return 0;
}
