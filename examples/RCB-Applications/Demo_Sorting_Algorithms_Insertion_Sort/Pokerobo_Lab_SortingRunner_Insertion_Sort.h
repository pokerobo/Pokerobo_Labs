#ifndef __POKEROBO_LAB_SORTING_RUNNER_INSERTION_SORT_H__
#define __POKEROBO_LAB_SORTING_RUNNER_INSERTION_SORT_H__

#include "Pokerobo_Lab_Sorting_Structure.h"

class InsertionSortingRunner: public SortingRunner {
  public:
    using SortingRunner::SortingRunner;
    InsertionSortingRunner(SampleManager *sample): SortingRunner(sample, "Insertion Sort") {}
    void sort();
};

#endif
