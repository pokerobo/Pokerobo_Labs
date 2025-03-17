#ifndef __POKEROBO_LAB_SORTING_RUNNER_BUBBLE_SORT_H__
#define __POKEROBO_LAB_SORTING_RUNNER_BUBBLE_SORT_H__

#include "Pokerobo_Lab_Sorting_Structure.h"

class BubbleSortingRunner: public SortingRunner {
  public:
    BubbleSortingRunner(SampleManager *sample, bool showStep = false): SortingRunner(sample, "Bubble Sort") {
      _showStep = showStep;
    }
    void sort();
  private:
    bool _showStep = true;
};

#endif
