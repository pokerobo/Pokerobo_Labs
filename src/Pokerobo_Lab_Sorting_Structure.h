#ifndef __POKEROBO_LAB_SORTING_STRUCTURE_H__
#define __POKEROBO_LAB_SORTING_STRUCTURE_H__

#include "Pokerobo_Lab_Display_Handler.h"

#define SAMPLE_MAX_SIZE 64

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


class SortingRunner: public ProgramSticker {
  public:
    SortingRunner(SampleManager *sample, char *title = "Sorting Algo"): ProgramSticker(title) {
      _sample = sample;
      _array = _sample->_array;
      _total = _sample->_total;
    }
    virtual void sort();
    int begin();
    int check(void* action, void* command=NULL);
    int close();
  protected:
    void swap(byte *i, byte *j);
    SampleManager *_sample = NULL;
    byte *_array;
    byte _total;
};

#endif
