#include "Pokerobo_Lab_Display_Handler.h"

#define SAMPLE_MAX_SIZE 64

void swap(byte *i, byte *j) {
  byte t = *i; *i = *j; *j = t;
}

class SampleManager {
  friend class SortingRunner;
  public:
    SampleManager(GeometryDisplayHandler* pen);
    void begin();
    void render();
    void draw();
  protected:
    void reset();
    void suffle();
    void swap(byte *i, byte *j);
  private:
    GeometryDisplayHandler* _pen = NULL;
    byte _array[SAMPLE_MAX_SIZE] = { 0 };
    byte _total = SAMPLE_MAX_SIZE;
};

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

class SortingRunner {
  public:
    SortingRunner(SampleManager *sample) {
      _sample = sample;
      _array = _sample->_array;
      _total = _sample->_total;
    }
    virtual void sort();
  protected:
    SampleManager *_sample = NULL;
    byte *_array;
    byte _total;
};

class BubbleSortingRunner: public SortingRunner {
  public:
    using SortingRunner::SortingRunner;
    void sort();
};

void BubbleSortingRunner::sort() {
  bool found;
  for(int i=0; i<_total - 1; i++) {
    found = false;
    for(int j=0; j < _total - i - 1; j++) {
      if (_array[j] > _array[j + 1]) {
        swap(&_array[j], &_array[j + 1]);
        found = true;
      }
      _sample->render();
    }
    if (!found) break;
  }
}

GeometryDisplayHandler pen;
SampleManager sample(&pen);
BubbleSortingRunner runner(&sample);

void setup() {
  Serial.begin(57600);
  pen.begin();
  sample.begin();
  runner.sort();
}

void loop() {}
