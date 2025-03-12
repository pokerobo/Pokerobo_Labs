#include "Pokerobo_Lab_SortingRunner_Heap_Sort.h"

void HeapSortingRunner::sort() {
  heapSort(_array, _total);
}

void HeapSortingRunner::heapSort(byte arr[], int n) {
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(arr, n, i);
    _sample->render();
  }

  for (int i = n - 1; i > 0; i--) {
    byte temp = arr[0];
    arr[0] = arr[i];
    arr[i] = temp;

    heapify(arr, i, 0);
    _sample->render();
  }
}

void HeapSortingRunner::heapify(byte arr[], int n, int i) {
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;

  if (l < n && arr[l] > arr[largest]) {
    largest = l;
  }

  if (r < n && arr[r] > arr[largest]) {
    largest = r;
  }

  if (largest != i) {
    byte temp = arr[i];
    arr[i] = arr[largest];
    arr[largest] = temp;

    heapify(arr, n, largest);
  }
}
