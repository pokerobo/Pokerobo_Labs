#ifndef __POKEROBO_LAB_SORTING_RUNNER_IMPL_H__
#define __POKEROBO_LAB_SORTING_RUNNER_IMPL_H__

#include "Pokerobo_Lab_Sorting_Structure.h"

class MergeSortingRunner: public SortingRunner {
  public:
    using SortingRunner::SortingRunner;
    void sort();
  private:
    void merge(byte arr[], int left, int mid, int right);
    void mergeSort(byte arr[], int left, int right);
};

#endif
