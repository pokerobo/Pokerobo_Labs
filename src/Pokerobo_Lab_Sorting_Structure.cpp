#include "Pokerobo_Lab_Sorting_Structure.h"

SampleManager::SampleManager(GeometryDisplayHandler* pen) {
  _pen = pen;
}

void SampleManager::begin() {
  reset();
}

void SampleManager::reset() {
  for(int i=0; i<_total; i++) {
    _array[i] = i;
  }
  suffle();
}

void SampleManager::suffle() {
  randomSeed(analogRead(A0));
  for (int i = _total-1; i>0; i--) {
    byte j = random(0, _total);
    swap(&_array[i], &_array[j]);
  }
}

void SampleManager::swap(byte *i, byte *j) {
  byte t = *i; *i = *j; *j = t;
}

void SampleManager::draw() {
  for(int i=0; i<_total; i++) {
    int x = 2*i + 1;
    _pen->drawLine(x, 63, x, 63 - _array[i]);
  }
}

void SampleManager::render() {
  _pen->firstPage();
  do {
    this->draw();
  } while (_pen->nextPage());
}

void SortingRunner::swap(byte *i, byte *j) {
  byte t = *i; *i = *j; *j = t;
}

int SortingRunner::begin() {
  _sample->reset();
  _sorted = false;
  return 0;
}

int SortingRunner::check(void* action, void* command) {
  if (!_sorted) {
    this->sort();
    _sorted = true;
  }
  return 0;
}

int SortingRunner::close() {
  return 0;
}

void SortingRunner::render() {
  _sample->render();
}
