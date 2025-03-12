#ifndef __POKEROBO_LAB_SORTING_RUNNER_IMPL_H__
#define __POKEROBO_LAB_SORTING_RUNNER_IMPL_H__

#include "Pokerobo_Lab_Sorting_Structure.h"

class SelectionSortingRunner: public SortingRunner {
  public:
    using SortingRunner::SortingRunner;
    BubbleSortingRunner(SampleManager *sample): SortingRunner(sample, "Selection Sort") {}
    void sort();
};

#endif
