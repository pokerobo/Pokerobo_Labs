#ifndef __POKEROBO_LAB_SORTING_RUNNER_QUICK_SORT_H__
#define __POKEROBO_LAB_SORTING_RUNNER_QUICK_SORT_H__

#include "Pokerobo_Lab_Sorting_Structure.h"

class QuickSortingRunner: public SortingRunner {
  public:
    QuickSortingRunner(SampleManager *sample): SortingRunner(sample, "Quick Sort") {}
    void sort();
  protected:
    void quickSort(byte arr[], int low, int high);
    int partition(byte arr[], int low, int high);
};

#endif
