/***********************************************/
/*****  Basic Array Related Problems  **********/
/***********************************************/
#include <cstdio>
#include <cstdlib>
#include <algorithm>

// Class for array of shifting elements
class ShiftArray {
protected:
  int* arr;
  int  size;
  int  usage;

public:
  // Check if array reached max limit
  bool isArrayFull(void) {
    return (usage == size);
  }

  // Display elements of array - O(N)
  void DisplayArray() {
    fflush(stdout);
    printf("\nValue:");
    for(int index = 0; index < usage; index++) {
      printf("\t%d", arr[index]);
    }
    printf("\nIndex:");
    for(int index = 0; index < usage; index++) {
      printf("\t%d", index);
    }
  }

  // Insert element at specific index - O(N)
  // Shift elements right --> (if already position occupied)
  bool InsertElement(const int position, const int value) {
    bool retval = false;
    if(isArrayFull()) {
      printf("\nArray is full cannot insert %d", value);
    } else {
      if((position < 0)||(position > usage)) {
        printf("\nInvalid index %d cannot insert %d", position, value);
      } else {
        // Traverse reverse from Usage to Position <--
        for(int index = usage; index > position; index--) {
          // Copy left element to current index
          arr[index] = arr[index - 1];
        }
        arr[position] = value;
        printf("\nInserted element at %d: %d", position, value);
        usage++;
        retval = true;
      }
    }
    return retval;
  }

  // Delete element at specific index - O(N)
  // Shift elements left <-- (to reoccupy deleted element position)
  bool DeleteElement(const int position) {
    int maxsize = usage - 1;
    bool retval = false;
    if((position < 0) || (position > maxsize)) {
      printf("\nInvalid index %d cannot delete", position);
    } else {
      const int value = arr[position];
      if(position != maxsize) {
        // Traverse forward from 0 to Position -->
        for(int index = position; index < usage; index++) {
          // Copy right element to current index
          arr[index] = arr[index + 1];
        }
      }
      printf("\nDeleted element at %d: %d", position, value);
      usage --;
      retval = true;
    }
    return retval;
  }

  // Constructor for allocating array
  ShiftArray(int count) {
    size  = count;
    usage = 0;
    arr   = (int*) malloc(sizeof(int) * size);
  }

  // Destructor for de-allocating array
  ~ShiftArray() {
    printf("\nFreeup");
    free(arr);
    arr = NULL;
  }
};

// Class for array of sorted elements (derived from ShiftArray)
class SortArray : public ShiftArray {
  int   maxlimit;

public:
  // Find closest (smaller) neighbour for element - O(LogN)
  int ClosestNeighbour(int low, int high, int target) {
    int retval = -1;
    if(low <= high) {
      int mid = low + (high - low) / 2;
      if(arr[mid] == target) {
        return mid;
      } else if (target < arr[mid]) {
        retval = ClosestNeighbour(low, (mid - 1), target);
      } else {
        retval = ClosestNeighbour((mid + 1), high, target);
      }
      // No neighbour found, check current < target
      if((retval == -1) && (arr[mid] < target)) {
        return mid;
      }
    } // End of if block
    return retval;
  }

  // Insert element into sorted array - O(LogN + N)
  bool AddElement(const int value) {
    // Find correct index for inserting new value - O(LogN)
    int index = ClosestNeighbour(0, (usage - 1), value);
    if(index == -1) {
      // Array empty or lowest index available
      index = 0;
    } else if(index == 0) {
      // To insert first, compare with existing element
      index = (value < arr[0]) ? 0 : 1;
    } else if(index == (usage - 1)) {
      // To insert last, compare with existing element
      index = (value < arr[usage - 1]) ? usage - 1 : usage;
    } else {
      // Lower index found, so insert at next index
      index = index + 1;
    }
    // Insert value at found index - O(N)
    return InsertElement(index, value);
  }

  // Delete element from sorted array - O(LogN + N)
  bool RemoveElement(const int value) {
    // Find exact index of element - O(LogN)
    int index = ClosestNeighbour(0, (usage - 1), value);
    // If element not found or closest neighbour found
    if((index == -1)||(arr[index] != value)) {
      printf("\nElement %d not found", value);
      return false;
    }
    // Delete element at found index - O(N)
    return DeleteElement(index);
  }

  // Constructor for SortArray and ShiftArray
  SortArray(const int count) : ShiftArray(count) {
    maxlimit = count;
  }

};

int main () {
  SortArray array(10);
  int arr[] = {8, 10, 2, 4, 12, 9};
  for(int index = 0; index < 6; index++) {
    array.AddElement(arr[index]);
  }
  array.DisplayArray();
  array.RemoveElement(12);
  array.DisplayArray();
  return 0;
}
