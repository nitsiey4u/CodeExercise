#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>
#include <fstream>
#include <unordered_map>

#define MAX_HEAP  10
#define MAX_SIZE  100

using namespace std;

void swap(int* a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// Struct for word info
struct WordInfo {
  string  word;
  int     frequency;
};
typedef struct WordInfo NODE;

// Find K most frequent words in file
class WordFile {
private:
  // Min-Heap to store K frequent words
  NODE**  MIN_HEAP;
  // Hash map to store word frequency
  unordered_map<string, NODE*> HASH_MAP;
  // File name used for processing
  fstream word_file;
  // K count of words to be maintained
  int     heap_size;
  // Actual usage of heap
  int     heap_usage;
  // Bool tracking usage of heap
  bool    heap_ready;

public:
  // Constructor
  WordFile(const int count) {
    heap_usage = 0;
    heap_size  = count;
    heap_ready = false;
    MIN_HEAP   = (NODE**) malloc(sizeof(NODE*) * heap_size);
  }

  // Check if heap usage has reached max limit
  bool isHeapFull() {
    return (heap_usage == heap_size);
  }

  // Swap heap nodes (pass by reference)
  void SwapValues(NODE* & ptr1, NODE* & ptr2) {
    NODE* temp = ptr1;
    ptr1 = ptr2;
    ptr2 = temp;
  }

  // Get frequency for specific word using heap node
  int GetFrequency(NODE* info) {
    return info->frequency;
  }

  // Set frequency for specific word using heap node
  void SetFrequency(NODE* & info, const int count) {
    info->frequency = count;
  }

  // Heap node percolate upwards
  void PercolateUpwards(const int index) {
    if((index >= 0) && (index < heap_usage)) {
      int current = index;
      int parent  = floor((current - 1)/ 2);
      if((parent >= 0) &&
         (GetFrequency(MIN_HEAP[current]) < GetFrequency(MIN_HEAP[parent]))) {
        SwapValues(MIN_HEAP[current], MIN_HEAP[parent]);
        PercolateUpwards(parent);
      }
    }
  }

  // Decrease key of newly inserted heap node
  void DecreaseKey(const int index, const int decrease) {
    SetFrequency(MIN_HEAP[index], decrease);
    PercolateUpwards(index);
  }

  // Call Min Heapify on index (ensuring smallest top element)
  void MinHeapify(const int index) {
    int parent = index;
    int left   = 2 * index + 1;
    int right  = 2 * index + 2;
    int small  = parent;
    // Check if left is smaller
    if((left < heap_usage) &&
       (GetFrequency(MIN_HEAP[left]) < GetFrequency(MIN_HEAP[small]))) {
      small = left;
    }
    // Check if right is smaller
    if((right < heap_usage) &&
       (GetFrequency(MIN_HEAP[right]) < GetFrequency(MIN_HEAP[small]))) {
      small = right;
    }
    // If small index different than parent
    if(small != parent) {
      SwapValues(MIN_HEAP[small], MIN_HEAP[parent]);
      MinHeapify(small);
    }
  }

  // Build Min Heap
  void BuildMinHeap(const int low, const int high) {
    int limit = floor((high - low)/2);
    for(int index = limit; index >=0; index--) {
      MinHeapify(index);
    }
  }

  // Insert new heap node (ensuring smallest top element)
  bool InsertWordInfo(NODE* info) {
    bool retval = false;
    if(isHeapFull()) {
      // Check if min heap is ready
      if(!heap_ready) {
        // Build min heap, as its not ready
        BuildMinHeap(0, (heap_usage - 1));
        heap_ready = true;
      }
      // Replace only when, new word frequency > root word frequency
      int root_frequency = GetFrequency(MIN_HEAP[0]);
      if(info->frequency > root_frequency) {
        // Insert new root and call min heapify
        MIN_HEAP[0] = info;
        MinHeapify(0);
        printf("\nInserted word %s [%d]",
               info->word.c_str(), info->frequency);
      } else {
        // Cannot insert least frequency word
        printf("\nCannot insert less frequent word %s [%d] (Root: %d)",
               info->word.c_str(), info->frequency, root_frequency);
        retval = false;
      }
    } else {
      // Simply insert heap nodes (build min heap later)
      MIN_HEAP[heap_usage] = info;
      heap_usage ++;
      retval = true;
    }
    return retval;
  }

  // Display all heap nodes (level order)
  void DisplayMinHeap() {
    printf("\nMinHeap");
    for(int index = 0; index < heap_usage; index++) {
      DisplayWordInfo(MIN_HEAP[index]);
    }
  }

  // Create word info
  NODE* CreateWordInfo(const string word) {
    NODE* info = (NODE*) malloc(sizeof(NODE));
    info->word      = word;
    info->frequency = 1;
    return info;
  }

  // Delete word info
  void DeleteWordInfo(NODE* info) {
    free(info);
    info = NULL;
  }

  // Display word info
  void DisplayWordInfo(NODE* info) {
    printf("\n%s -> %d", info->word.c_str(), info->frequency);
  }

  // Read file and intialize hash map with word frequencies
  bool ReadFile(const string file) {
    bool retval = false;
    word_file.open(file);
    if(word_file.is_open()) {
      string key_word;
      while(word_file >> key_word) {
        // Check whether word is visited before
        if(HASH_MAP.find(key_word) == HASH_MAP.end()) {
          // For newly visited word, add new word to hashmap
          NODE* val_info = CreateWordInfo(key_word);
          HASH_MAP[key_word] = val_info;
        } else {
          // For re-visited word, update frequency of word
          NODE* val_info = HASH_MAP[key_word];
          val_info->frequency ++;
        }
      }
      word_file.close();
      retval = true;
    }
    return retval;
  }

  // Find K frequent words
  void FindKFrequentWords(int count) {
    // Iterate over all words
    for(auto itr : HASH_MAP) {
      // Insert word into min-heap
      // This ensures only most frequent words remain in heap
      InsertWordInfo(itr.second);
    }
    DisplayMinHeap();
    // Traverse min-heap in reverse to get most frequent words
    printf("\n%d most frequent words are: ", count);
    int index = heap_usage - 1;
    while((index >=0) & (count > 0)) {
      DisplayWordInfo(MIN_HEAP[index]);
      index --;
      count --;
    }
  }

  // Erase hash map
  void DeleteWordMap() {
    for(auto itr : HASH_MAP) {
      //printf("\nDeleting %s", itr.first.c_str());
      DeleteWordInfo(itr.second);
    }
  }

  // Display hash map
  void DisplayWordMap() {
    printf("\nWord Frequency Map");
    for(auto itr : HASH_MAP) {
      DisplayWordInfo(itr.second);
    }
  }

  // Destructor
  ~WordFile() {
    // Free dynamically allocated array of pointers
    free(MIN_HEAP);
    MIN_HEAP = NULL;
  }
};



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
