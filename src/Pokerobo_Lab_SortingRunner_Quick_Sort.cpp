#include "Pokerobo_Lab_SortingRunner_Quick_Sort.h"

void QuickSortingRunner::sort() {
  quickSort(_array, 0, _total - 1);
}

void QuickSortingRunner::quickSort(byte arr[], int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

int QuickSortingRunner::partition(byte arr[], int low, int high) {
  byte pivot = arr[high];
  
  int i = low - 1;

  for (int j = low; j <= high - 1; j++) {
    if (arr[j] < pivot) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }

  swap(&arr[i + 1], &arr[high]);

  render();

  return i + 1;
}
