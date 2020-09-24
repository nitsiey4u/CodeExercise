#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include <string>
#define MAX_SIZE 100

void swap(int* a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

class MaxHeap {
private:
  int max_size;
  int heap_size;
  int heap[MAX_SIZE];
public:
  // Constructor
  MaxHeap(int arr[], int size) {
    max_size = size;
    heap_size = size;
    for(int index = 0; index < max_size; index++) {
      heap[index] = arr[index];
      // For min-heap use code below
      // heap[index] = -1 * arr[index];
    }
  }

  // Max heapify - O(Log N)
  void max_heapify(const int index, const int size) {
    if(index < size) {
      int largest = index;          // parent
      int left    = 2 * index + 1;  // left child
      int right   = 2 * index + 2;  // right child
      // Compare parent with left child
      if((left < size) && (heap[largest] < heap[left])) {
        largest = left;
      }
      // Compare parent with right child
      if((right < size) && (heap[largest] < heap[right])) {
        largest = right;
      }
      // Swap with largest child and call max-heapify
      if(largest != index) {
        swap(&heap[largest], &heap[index]);
        max_heapify(largest, size);
      }
    }
  }

  // Display elements of heap - O(N)
  void display_heap(const char* str) {
    printf("\n%s: ", str);
    for(int index = 0; index < heap_size; index++) {
      printf("\t%d", heap[index]);
      // For min-heap use code below
      // printf("\t%d", -1 * heap[index]);
    }
  }

  // Build max heap - O(N)
  void build_max_heap() {
    int internal = floor(((heap_size)/2) - 1);
    // Iterate over non-leaf nodes to build max heap
    for(int index = internal; index >=0; index --) {
      max_heapify(index, heap_size);
    }
  }

  // Heap sort algorithm - O(N LogN)
  void sort_keys() {
    const int prev_size = heap_size;
    // Build max heap - O(N)
    build_max_heap();
    display_heap("Max Heap");
    // Loop until we process all elements - O(N)
    while(heap_size > 1) {
      // Swap largest element at root with last element of heap
      swap(&heap[0], &heap[heap_size-1]);
      // Decrement heap size
      heap_size --;
      // Max heapify new root - O(LogN)
      max_heapify(0, heap_size);
    }
    heap_size = prev_size;
  }

  // Extract max key from heap - O(1)
  int extract_max() {
    if(heap_size > 0) {
      return heap[0];
    }
    printf("\nHeap is empty.");
    return -1;
  }

  // Compare index with its parent - O(LogN)
  void percolate_upwards(const int child) {
    if(child > 0) {
      int parent = floor((child - 1)/2);
      if((parent >= 0) && (heap[parent] < heap[child])) {
        swap(&heap[parent], &heap[child]);
        percolate_upwards(parent);
      }
    }
  }

  // Insert new key into heap - O(LogN)
  void insert_key(const int newkey) {
    int index = heap_size;
    heap[index] = newkey;
    // For min-heap use code below
    // heap[index] = -1 * newkey;
    heap_size++;
    percolate_upwards(index);
  }

  // Delete key from max heap
  void delete_key() {
    if(heap_size > 0) {
      int key = heap[0];
      printf("\nDeleted key: %d", key);
      // Assign last element of heap to root
      heap[0] = heap[heap_size - 1];
      // Decrement heap size
      heap_size --;
      // Call max heapify on new root
      max_heapify(0, heap_size);
    } else {
      printf("\nHeap is empty.");
    }
  }

};

int main(){
  int arr[] = {1, 3, 5, 6, 10, 8};
  int size  = sizeof(arr)/sizeof(int);
  MaxHeap HEAP(arr, size);
  HEAP.display_heap("Binary Heap");
  HEAP.build_max_heap();
  HEAP.display_heap("Max Heap");

  HEAP.insert_key(20);
  HEAP.display_heap("New Heap");

  HEAP.sort_keys();
  HEAP.display_heap("Sorted List");

  //printf("\nMaximum: %d", HEAP.extract_max());
  // for(int index = 1; index <= size; index++) {
  //   HEAP.delete_key();
  //   HEAP.display_heap("Updated heap");
  // }

  //HEAP.sort_keys();
  //HEAP.display_heap("Sorted List");

  return 0;
}
