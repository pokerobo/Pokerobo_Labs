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

void AcceGyroRenderer::update(int16_t value) {
  _value = value;
  int2str_(_valueStr, _value);

  if (_minAcc > _value) {
    _minAcc = _value;
    int2str_(_minAccStr, _minAcc);
  }

  if (_maxAcc < _value) {
    _maxAcc = _value;
    int2str_(_maxAccStr, _maxAcc);
  }
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

  int16_t pos = map(_value, _minAcc, _maxAcc, 3, 64 - 3);
  _pen->drawTriangle(127 - 5, pos, 127, pos - 3, 127, pos + 3);
  _pen->drawStr(127 - 6 - 6*_charWidth, pos + 3, _valueStr);
}

char* AcceGyroRenderer::int2str_(char* buffer, int16_t value) {
  sprintf(buffer, "% 5d", value);
  return buffer;
}

//-------------------------------------------------------------------------------------------------

void AcceGyroDiagram::draw() {
  AcceGyroRenderer::draw();
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
