#ifndef __POKEROBO_LAB_SORTING_RUNNER_HEAP_SORT_H__
#define __POKEROBO_LAB_SORTING_RUNNER_HEAP_SORT_H__

#include "Pokerobo_Lab_Sorting_Structure.h"

class HeapSortingRunner: public SortingRunner {
  public:
    using SortingRunner::SortingRunner;
    HeapSortingRunner(SampleManager *sample): SortingRunner(sample, "Heap Sort") {}
    void sort();
  protected:
    void heapSort(byte arr[], int n);
    void heapify(byte arr[], int n, int i);
};

#endif
