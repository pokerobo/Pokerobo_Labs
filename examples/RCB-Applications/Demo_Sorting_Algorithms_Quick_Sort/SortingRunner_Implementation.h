#ifndef __POKEROBO_LAB_SORTING_RUNNER_IMPL_H__
#define __POKEROBO_LAB_SORTING_RUNNER_IMPL_H__

#include "Pokerobo_Lab_Sorting_Structure.h"

class QuickSortingRunner: public SortingRunner {
  public:
    using SortingRunner::SortingRunner;
    void sort();
  protected:
    void quickSort(byte arr[], int low, int high);
    int partition(byte arr[], int low, int high);
};

#endif
