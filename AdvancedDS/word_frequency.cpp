/**********************************************************
  Find K Most Frequent words from file using DS
  Ordered Map : Word(Key), Node*(Heap) pairs
  Min Heap    : Array of K Nodes (most frequent words)
***********************************************************/
#include <fstream>
#include <cstdio>
#include <string>
#include <unordered_map>

#define MAX_HEAP  10
using namespace std;

// Structure for word information
struct WordInfo {
  string  word;
  int     frequency;
};
typedef struct WordInfo NODE;

// Class recording K frequent words
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

  bool isHeapFull() {
    return (heap_usage == heap_size);
  }

  void SwapValues(NODE* & ptr1, NODE* & ptr2) {
    NODE* temp = ptr1;
    ptr1 = ptr2;
    ptr2 = temp;
  }

  int GetFrequency(NODE* info) {
    return info->frequency;
  }

  void SetFrequency(NODE* & info, const int count) {
    info->frequency = count;
  }

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

  void DecreaseKey(const int index, const int decrease) {
    SetFrequency(MIN_HEAP[index], decrease);
    PercolateUpwards(index);
  }

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

  void BuildMinHeap(const int low, const int high) {
    int limit = floor((high - low)/2);
    for(int index = limit; index >=0; index--) {
      MinHeapify(index);
    }
  }

  bool InsertWordInfo(NODE* info) {
    bool retval = false;
    if(isHeapFull()) {
      // Check if min heap is ready
      if(!heap_ready) {
        // Build min heap, as its not ready
        BuildMinHeap(0, (heap_usage - 1));
        heap_ready = true;
      }
      // Replace element
      int root_frequency = GetFrequency(MIN_HEAP[0]);
      if(info->frequency > root_frequency) {
        MIN_HEAP[0] = info;
        MinHeapify(0);
        printf("\nInserted word %s [%d]",
               info->word.c_str(), info->frequency);
      } else {
        printf("\nCannot insert less frequent word %s [%d] (Root: %d)",
               info->word.c_str(), info->frequency, root_frequency);
        retval = false;
      }
    } else {
      // Simply insert values
      MIN_HEAP[heap_usage] = info;
      heap_usage ++;
      retval = true;
    }
    return retval;
  }

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

  // Read file and intialize map
  bool ReadFile(const string file) {
    bool retval = false;
    word_file.open(file);
    if(word_file.is_open()) {
      string key_word;
      while(word_file >> key_word) {
        if(HASH_MAP.find(key_word) == HASH_MAP.end()) {
          NODE* val_info = CreateWordInfo(key_word);
          HASH_MAP[key_word] = val_info;
        } else {
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
    for(auto itr : HASH_MAP) {
      InsertWordInfo(itr.second);
    }
    DisplayMinHeap();
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
    free(MIN_HEAP);
    MIN_HEAP = NULL;
  }
};

int main() {
  WordFile object(10);
  const string file = "/tmp/text.log";
  if(!object.ReadFile(file)) {
    printf("\nCannot read file %s", file.c_str());
  } else {
    object.DisplayWordMap();
  }
  object.FindKFrequentWords(5);
  //object.DisplayMinHeap();
  object.DeleteWordMap();
  return 0;
}
