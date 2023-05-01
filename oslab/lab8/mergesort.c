#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>


int arr[] = {6, 5, 12, 10, 9, 1};
int size = sizeof(arr) / sizeof(arr[0]);


typedef struct {
  int high;
  int low;
} bruh;

// Merge two subarrays L and M into arr
void merge(int p, int q, int r) {

  // Create L ← A[p..q] and M ← A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];

  // Maintain current index of sub-arrays and main array
  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(void* s2) {

  bruh* s1 = (bruh *)s2;

  int l = s1->low;
  int r = s1->high;

  if (l < r) {

    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;

    pthread_t t1, t2;

    bruh d1;
    bruh d2;

    d1.low = l;
    d1.high = m;

    d2.low = m+1;
    d2.high = r;

    pthread_create(&t1, NULL, mergeSort, (void *)&d1);
    pthread_create(&t2, NULL, mergeSort, (void *)&d2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    //mergeSort(arr, l, m);
    //mergeSort(arr, m + 1, r);

    // Merge the sorted subarrays
    merge(l, m, r);
  }
}

// Print the array
void printArray(int size) {
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

// Driver program
int main() {
  
  bruh yeet;
  yeet.low = 0;
  yeet.high = size - 1;
  mergeSort(&yeet);

  printf("Sorted array: \n");
  printArray(size);
}