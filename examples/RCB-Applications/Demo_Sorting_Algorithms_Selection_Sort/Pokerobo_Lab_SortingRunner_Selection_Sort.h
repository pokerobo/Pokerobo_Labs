#ifndef __POKEROBO_LAB_SORTING_RUNNER_SELECTION_SORT_H__
#define __POKEROBO_LAB_SORTING_RUNNER_SELECTION_SORT_H__

#include "Pokerobo_Lab_Sorting_Structure.h"

class SelectionSortingRunner: public SortingRunner {
  public:
    using SortingRunner::SortingRunner;
    SelectionSortingRunner(SampleManager *sample): SortingRunner(sample, "Selection Sort") {}
    void sort();
};

#endif
