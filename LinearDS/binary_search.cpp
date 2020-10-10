/***********************************************/
/*********** Binary Search Related	 ***********/
/***********************************************/
#include <cstdio>
#include <string>
#include <cstdlib>
#include <climits>
#include <cmath>

// Predefined constants
#define MAX_TMP_SIZE		5
#define MAX_VAL_SIZE    4
#define BOOL(val)       ((val) ? "True" : "False")

typedef unsigned long long int  ullint_t;   // 8 bytes unsigned
typedef long long int           llint_t;    // 8 bytes signed
typedef unsigned int            uint_t;     // 4 bytes unsigned

// Helper for quick sort
int comparator(const void* a, const void *b) {
  return (*(int*)a - *(int*)b);
}

// Helper to display array
void display_array(const char* title, int* arr, int size) {
	int index;
	printf("\n%s => ", title);
	printf("\nValue:");
	for(index = 0; index < size; index++) {
		printf("\t%d", arr[index]);
	}
	printf("\nIndex:");
	for(index = 0; index < size; index++) {
		printf("\t%d", index);
	}
	printf("\n");
}

// Binary Search Implementation (iterative)
int binary_search_iterative(int* arr, int size, int target) {
	int low = 0;
	int high = (size - 1);
	while (low <= high) {
		int mid = low + ((high - low) >> 1);
		if (arr[mid] == target)
			return mid;
		else {
			if(arr[mid] < target)
				low = mid + 1;
			else
				high = mid - 1;
		}
	}
	return -1;
}

// Binary Search Implementation (recursive)
int binary_search(int* arr, int low, int high, int target) {
	if (low <= high) {
		int mid = low + (high - low) / 2;
		if(arr[mid] == target)
			return mid;
		else if(arr[mid] < target)
			return binary_search(arr, (mid + 1), high, target);
		else
			return binary_search(arr, low, (mid - 1), target);
	}
	return -1;
}

// Find first index of number using binary search (recursive)
int binary_search_first(int* arr, int low, int high, int size, int target) {
	if(low <= high) {
		int mid = low + (high - low) / 2;
		// check if previous index is same or not
		if(((mid == 0) || (arr[mid - 1] < target)) && (arr[mid] == target))
			return mid;
		else if(arr[mid] < target)
			return binary_search_first(arr, (mid + 1), high, size, target);
		else
			return binary_search_first(arr, low, (mid - 1), size, target);
	}
	return -1;
}

// Find last index of number using binary search (recursive)
int binary_search_last(int* arr, int low, int high, int size, int target) {
	if (low <= high) {
		int mid = low + (high - low)/2;
		if(((mid == size) || (arr[mid+1] > target))  && (arr[mid] == target))
			return mid;
		else if (arr[mid] > target)
			return binary_search_last(arr, low, (mid - 1), size, target);
		else
		 	return binary_search_last(arr, (mid + 1), high, size, target);
	}
	return -1;
}

// Find range of index for number using binary search
int* target_range(int* arr, int size, int target) {
	int* range = (int*)malloc(sizeof(int) * 2);
	range[0] = binary_search_first(arr, 0, (size - 1), (size - 1), target);
	range[1] = (range[0] == -1) ? -1 : binary_search_last(arr, 0, (size - 1), (size - 1), target);
	return range;
}

// Find frequency count of target - O(LogN)
int frequency_count(int* arr, int size, int target) {
  // Find start index of target
  int lower = binary_search_first(arr, 0, (size - 1), (size - 1), target);
  if(lower == -1) {
    // If target itself is missing from array
    return -1;
  }
  // Find last index of target
  int upper = binary_search_last(arr, 0, (size - 1), (size - 1), target);
  return (upper - lower + 1);
}

// Find pairs of value with matching sum - O(NlogN)
void sum_pairs(int arr[], int size, const int sum) {
  // Sort array elements - O(LogN)
	qsort(arr, size, sizeof(int), comparator);
  // Iterating over array - O(N)
  for(int index = 0; index < size; index++) {
    int target = (sum - arr[index]);
    // Binary search to find target sum - O(LogN)
    int posval = binary_search(arr, index, (size - 1), target);
    if((posval != -1) && (posval != index)) {
      printf("\nSum pair: %d %d", arr[index], arr[posval]);
    }
  }
}

// Find triplets matching sum using binary search - O(N2)
void sum_triplets(int arr[], int size, const int sum) {
  // Sort array elements - O(LogN)
	qsort(arr, size, sizeof(int), comparator);
  display_array("Sorted", arr, size);
  // Iterate over array elements - O(N)
  for(int outer = 0; outer < (size - 2); outer++) {
    int match_sum = sum - arr[outer];
    // Iterate over array elements - O(N)
    for(int inner = (outer + 1); inner < (size - 1); inner++) {
      int target = match_sum - arr[inner];
      // Binary search to find last element of triplet - O(LogN)
      int index  = binary_search(arr, (inner + 1), (size - 1), target);
      if(index != -1) {
          printf("\nFound triplet:\t%d\t%d\t%d",
                arr[outer], arr[inner], target);
      }
    } // End of inner loop
  } // End of outer loop
}

// Find local minima index in UNSORTED array - O(LogN)
int local_minima(int arr[], int low, int high, int size) {
  if(low <= high) {
    // Get middle index
    int mid = low + (high - low)/2;
    // Check if middle index is only element in array
    if(size == 0) {
      return mid;
    }
    // Start of array - compare middle with right neighbour (mid + 1)
    // End of array - compare middle with left neighbour (mid - 1)
    // Middle of array - compare middle with left and right neighbours
    else if((mid == 0) && (arr[mid] <= arr[mid + 1]) ||
            (mid == size) && (arr[mid] <= arr[mid - 1]) ||
            (arr[mid] <= arr[mid + 1]) && (arr[mid] <= arr[mid - 1])) {
      return mid;
    }
    // If left neigbour (mid - 1) is smaller than current
    // Local minima must be in left half <--
    else if(arr[mid - 1] < arr[mid]) {
      return local_minima(arr, low, (mid - 1), size);
    }
    // If right neigbour (mid + 1) is smaller than current
    // Local minima must be in right half -->
    else {
      return local_minima(arr, (mid + 1), high, size);
    }
  }
  return -1;
}

// Find local maxima or peek index in UNSORTED array - O(LogN)
int local_maxima(int arr[], int low, int high, int size) {
  if(low <= high) {
    // Get middle index
    int mid = low + (high - low)/2;
    // Check if middle index is only element in array
    if(size == 0) {
      return mid;
    }
    // Start of array - compare middle with right neighbour (mid + 1)
    // End of array - compare middle with left neighbour (mid - 1)
    // Middle of array - compare middle with left and right neighbours
    else if((mid == 0) && (arr[mid] >= arr[mid + 1]) ||
       (mid == size) && (arr[mid] >= arr[mid - 1]) ||
       (arr[mid] >= arr[mid + 1]) && (arr[mid] >= arr[mid - 1])) {
      return mid;
    }
    // If left neigbour (mid - 1) is greater than current
    // Local maxima must be in left half <--
    else if(arr[mid - 1] > arr[mid]) {
      return local_maxima(arr, low, (mid - 1), size);
    }
    // If right neigbour (mid + 1) is greater than current
    // Local maxima must be in right half -->
    else {
      return local_maxima(arr, (mid + 1), high, size);
    }
  }
  return -1;
}

// Find max element (peak) increasing decreasing array - O(LogN)
// Example: 5, 10, 20, 4, 2 (Peak - 20)
int peaked_maximum(int arr[], int low, int high, int size) {
  if(low <= high) {
    int mid = low + (high - low)/2;
    // Array size 0, return middle element
    if(size == 0) {
      return mid;
    }
    // Reached start of array compare with right (mid + 1) neigbour
    // Example: 3, 2, 1
    else if((mid == 0) && (arr[mid] > arr[mid + 1])) {
      return mid;
    }
    // Reached end of array compare with left (mid - 1) neigbour
    // Example: 1, 2, 3
    else if((mid == size) && (arr[mid] > arr[mid - 1])) {
      return mid;
    }
    // Reached middle of array compare with left and right neigbours
    // Example: 1, 5, 10, 7, 2
    else if((arr[mid] > arr[mid - 1]) && (arr[mid] > arr[mid + 1])) {
      return mid;
    }
    // If current < next (recurse right half -->)
    else if(arr[mid] < arr[mid + 1]) {
      return peaked_maximum(arr, (mid + 1), high, size);
    }
    // If previous > current (recurse left half <--)
    else {
      return peaked_maximum(arr, low, (mid - 1), size);
    }
  }
  return -1;
}

// Ceil - MIN (Elements greater than or equal to Target) - O(LogN)
// Example: 1, 2, 8, 10  (Ceil[5]: 8, Ceil[2]: 2, Ceil[11]: -1)
int ceil_minimum(int arr[], int low, int high, int target) {
  int retval = -1;
  if(low <= high) {
    // Get first minimum element which is greater than target
    if(target <= arr[low]) {
      // Low index indicates minimum element in sorted array
      return low;
    }
    // Continue with regular binary search
    int mid = low + (high - low) / 2;
    if(arr[mid] == target) {
      // If target matches middle, ceil found
      return mid;
    } else if(target < arr[mid]) {
      // Check index of left search
      retval = ceil_minimum(arr, low, (mid - 1), target);
      if((retval == -1) && (target <= arr[mid])) {
        // If ceil not found, check middle >= target
        return mid;
      }
    } else {
      // Check index of right search
      retval = ceil_minimum(arr, (mid + 1), high, target);
      if((retval == -1) && (target <= arr[mid])) {
        // If ceil not found, check middle >= target
        return mid;
      }
    }
  }
  // Ceil not found
  return retval;
}

// Floor - MAX (Elements smaller than or equal to Target) - O(LogN)
// Example: 1, 2, 8, 10  (Floor[5]: 2, Floor[1]: 1, Floor[0]: -1)
int floor_maximum(int arr[], int low, int high, int target) {
  int retval = -1;
  if(low <= high) {
    // Get last maximum element which is smaller than target
    if(arr[high] <= target) {
      // High index indicates maximum element in sorted array
      return high;
    }
    // Continue with regular binary search
    int mid = low + (high - low) / 2;
    if(arr[mid] == target) {
      // If target matches middle, floor found
      return mid;
    } else if(target < arr[mid]) {
      // Check index of left search
      retval = floor_maximum(arr, low, (mid - 1), target);
      if((retval == -1) && (arr[mid] <= target)) {
        // If floor not found, check middle <= target
        return mid;
      }
    } else {
      // Check index of right search
      retval = floor_maximum(arr, (mid + 1), high, target);
      if((retval == -1) && (arr[mid] <= target)) {
        // If floor not found, check middle <= target
        return mid;
      }
    }
  }
  // Floor not found
  return retval;
}

// Is array sorted in ascending order - O(N)
bool is_ascending(int* arr, const int low, const int high) {
  if(low <= high) {
    int mid = low + (high - low)/2;
    //printf("\nLow: %d High: %d Mid: %d", arr[low], arr[high], arr[mid]);
    if(low == high) {
      return true;
    }
    else if (mid == low) {
      if(arr[mid] > arr[mid + 1]) return false;
    }
    else if (mid == high) {
      if(arr[mid-1] > arr[mid]) return false;
    }
    else {
      if((arr[mid - 1] <= arr[mid]) && (arr[mid] <= arr[mid + 1])) {
        return is_ascending(arr, low, (mid - 1)) &&
               is_ascending(arr, (mid + 1), high);
      } else {
        return false;
      }
    }
  }
  return true;
}

// Is array sorted in descending order - O(N)
bool is_descending(int* arr, const int low, const int high) {
  if(low <= high) {
    int mid = low + (high - low)/2;
    if(low == high) {
      return true;
    }
    else if (mid == low) {
      if(arr[mid] < arr[mid + 1]) return false;
    }
    else if (mid == high) {
      if(arr[mid-1] < arr[mid]) return false;
    }
    else {
      if((arr[mid - 1] >= arr[mid]) && (arr[mid] >= arr[mid + 1])) {
        return is_descending(arr, low, (mid - 1)) &&
               is_descending(arr, (mid + 1), high);
      } else {
        return false;
      }
    }
  }
  return true;
}

// Check if array is sorted (ascending or descending) - O(N)
bool is_sorted(int* arr, const int size) {
  return is_ascending(arr, 0, (size - 1)) ||
         is_descending(arr, 0, (size - 1));
}

// Find target element in rotated sorted array - O(LogN)
int rotated_search(int arr[], int low, int high, int target) {
  if(low <= high) {
    int mid = low + (high - low)/2;
    if(arr[mid] == target) {
      return mid;
    }
    // Left array is sorted
    if(arr[low] <= arr[mid]) {
      // Left array is sorted
      if((arr[low] <= target) && (target <= arr[mid])) {
        // Target lies in left half <--
        return rotated_search(arr, low, (mid - 1), target);
      } else {
        // Target lies in right half -->
        return rotated_search(arr, (mid + 1), high, target);
      }
    }
    // Right array is sorted
    else {
      if((arr[mid] <= target) && (target <= arr[high])) {
        // Target lies in right half -->
        return rotated_search(arr, (mid + 1), high, target);
      } else {
        // Target lies in left half <--
        return rotated_search(arr, low, (mid - 1), target);
      }
    }
  }
  return -1;
}

// Find minimum element in sort rorated array - O(LogN)
// Sorted array element condition left < middle < right
// Main condition for min element is left > middle, return middle
int rotated_minimum(int arr[], int low, int high) {
  if(low <= high) {
    int mid = low + (high - low) / 2;
    if(low == high) {
      printf("Reached min: %d", arr[high]);
      return high;
    }
    // Current element is smallest than left and right, return current
    else if((arr[mid - 1] > arr[mid]) && (arr[mid] < arr[mid + 1])) {
      return mid;
    }
    // Current element is greatest than left and right, return right
    else if((arr[mid - 1] < arr[mid]) && (arr[mid] > arr[mid + 1])) {
      return mid + 1;
    }
    // Right and High elements are greater than current element
    else if((arr[mid] < arr[mid + 1]) && (arr[mid] < arr[high])) {
      // Find smaller elements by recursing left <--
      return rotated_minimum(arr, low, (mid - 1));
    }
    // Low and Left elements are smaller than current element
    else if((arr[low] < arr[mid]) && (arr[mid - 1] < arr[mid])) {
      // Find smaller elements based on low-high comparison
      if(arr[low] < arr[high]) {
        // Low < High, recurse left <--
        return rotated_minimum(arr, low, (mid - 1));
      } else {
        // Low > High, recurse right -->
        return rotated_minimum(arr, (mid + 1), high);
      }
    }
  }
  return -1;
}

// Find maximum element in rorated sort array - O(LogN)
// Sorted array element condition left < middle < right
// Main condition for max element is middle > right, return middle
int rotated_maximum(int arr[], int low, int high) {
  if(low <= high) {
    int mid = low + (high - low) / 2;
    if(low == high) {
      printf("\nReached max: %d", arr[low]);
      return low;
    }
    // Current element is greatest than left and right, return current
    else if((arr[mid - 1] < arr[mid]) && (arr[mid] > arr[mid + 1])) {
      // Current element is greatest
      return mid;
    }
    // Current element is smallest than left and right, return left
    else if((arr[mid - 1] > arr[mid]) && (arr[mid] < arr[mid + 1])) {
      // Previous element is greatest
      return mid - 1;
    }
    // Right and High elements are greater than current element
    else if((arr[mid] < arr[mid + 1]) && (arr[mid] < arr[high])) {
      // Find greater elements based on low-high comparison
      if(arr[low] < arr[high]) {
        // Low < High, recurse right -->
        return rotated_maximum(arr, (mid + 1), high);
      } else {
        // Low > High, recurse left <--
        return rotated_maximum(arr, low, (mid - 1));
      }
    }
    // Low and Left elements are smaller than current element
    else if((arr[low] < arr[mid]) && (arr[mid - 1] < arr[mid])) {
      // Find greater elements by recursing right -->
      return rotated_maximum(arr, (mid + 1), high);
    }
  }
  return -1;
}

// Check if given array is rotated sorted - O(N)
// Main condition check:
// Last element is smaller than First element of array
// Arrays before/after Rotational Pivot (Largest) is ascending sorted
bool is_rotated_sorted(int arr[], int size) {
  // Find rotational pivot largest value in array - O(LogN)
  int low   = 0;        // First element
  int high  = size - 1; // Last element
  int pivot = rotated_maximum(arr, low, high);
  int left  = (pivot + (size - 1)) % size;
  int right = (pivot + 1) % size;
  printf("\nLeft: %d\tPivot: %d\tRight: %d",
         arr[left], arr[pivot], arr[right]);
  // Check if pivot is greater than left and right
  // Also last element is smaller than first element
  if((arr[left] < arr[pivot]) && (arr[pivot] > arr[right]) &&
     (arr[high] < arr[low])) {
    // Array before/after pivot should be ascending sorted - O(N)
    return is_ascending(arr, low, (pivot - 1)) &&
           is_ascending(arr, (pivot + 1), high);
  }
  return false;
}

// Main driver
int main() {
  // int arr[] = {2, 1, 5, 7, -1, 5, 4};
  // int size  = sizeof(arr)/sizeof(arr[0]);
  // sum_pairs(arr, size, 6);

  int arr[] = {0, 4, 45, 6, 10, 8};
  int size  = sizeof(arr)/sizeof(arr[0]);
  display_array("Display", arr, size);
  sum_triplets(arr, size, 18);

  // int arr[]  = {9, 6, 3, 4, 5, 7, 4};
  // int size   = sizeof(arr)/sizeof(arr[0]);
  // int minima = local_minima(arr, 0, (size - 1), (size - 1));
  // printf("\nLocal Minima: %d (Value: %d)", minima, arr[minima]);
  // int maxima = local_maxima(arr, 0, (size - 1), (size - 1));
  // printf("\nLocal Maxima: %d (Value: %d)", maxima, arr[maxima]);
  // int arr[] = {2, 3, 4, 1};
  // int size  = sizeof(arr)/sizeof(arr[0]);
  // int min   = rotated_minimum(arr, 0, (size - 1), (size - 1));
  // printf("\nMin Val: %d", (min == -1) ? 0 : arr[min]);
  // int arr[] = {4, 5, 1, 2, 3};
  // int size  = sizeof(arr)/sizeof(arr[0]);
  // int max   = rotated_maximum(arr, 0, (size - 1), (size - 1));
  // printf("\nMin Val: %d", (max == -1) ? 0 : arr[max]);
  // const double ratio = (1 + sqrt(5))/2;
  // int outer, inner, counter;
  // int array[MAX_VAL_SIZE];
  // for(outer = 0; outer < MAX_VAL_SIZE; outer++) {
  //   int value = 5;
  //   for(inner = outer, counter = 0; counter < MAX_VAL_SIZE; counter++) {
  //     array[inner] = value;
  //     value = value * ratio;
  //     inner = (inner + 1) % MAX_VAL_SIZE;
  //   }
  //   display_array("Array", array, MAX_VAL_SIZE);
  //   int min = rotated_minimum(array, 0, (MAX_VAL_SIZE - 1), (MAX_VAL_SIZE - 1));
  //   printf("\nMin Val: %d", (min == -1) ? 0 : array[min]);
  //   int max = rotated_maximum(array, 0, (MAX_VAL_SIZE - 1), (MAX_VAL_SIZE - 1));
  //   printf("\nMax Val: %d", (max == -1) ? 0 : array[max]);
  // }

  // int arr[] = {8, 10, 20, 80, 100, 200, 400, 500, 3, 2, 1};
  // int arr[] = {1, 3, 50, 10, 9, 7, 6};
  // int arr[] = {10, 20, 30, 40, 50};
  // int arr[] = {120, 100, 80, 20, 0};
  // int size  = sizeof(arr)/sizeof(arr[0]);
  // int peak  = peaked_maximum(arr, 0, (size - 1), (size - 1));
  // printf("\nMax Val: %d", (peak == -1) ? 0 : arr[peak]);

  // int arr[] = {1, 2, 8, 10, 10, 12, 19};
  // int arr[] = {1, 2, 8, 10, 12, 19};
  // int size  = sizeof(arr)/sizeof(arr[0]);
  // int floor  = floor_maximum(arr, 0, (size - 1), 0);
  // printf("\nFloor: %d", (floor == -1) ? -1 : arr[floor]);
  // int ceil  = ceil_minimum(arr, 0, (size - 1), 0);
  // printf("\nCeil: %d", (ceil == -1) ? -1 : arr[ceil]);

  // int arr[] = {3, 4, 5, 1, 2};
  // int size  = sizeof(arr)/sizeof(arr[0]);
  // printf("\nSorted: %s", BOOL(is_ascending(arr, 0, 4)));

  // int arr[] = {2, 3, 4, 1};
  // int arr[] = {4, 3, 2, 1};
  // int arr[] = {5, 1, 2, 3}; // Fix
  // int arr[] = {5, 1, 2, 3, 4}; // Fix
  // int arr[] = {3, 4, 5, 1, 2};
  // int arr[] = {2, 1, 3, 5};
  //int arr[] = {4, 1, 2, 3};
  // int arr[] = {2, 3, 4, 5, 1};
  // int arr[] = {1, 2, 3, 4};
  // int arr[] = {8, 9, 1, 2, 3, 4, 5, 6, 7};
  // int size  = sizeof(arr)/sizeof(arr[0]);
  // display_array("Array", arr, size);
  // // printf("\nRotated: %s", BOOL(is_rotated(arr, 0, (size - 1), (size - 1))));
  // printf("\nIndex: %d", rotated_search(arr, 0, (size - 1), 7));

  // int arr[] = {8, 9, 1, 2, 3, 4, 5, 6, 7};

  // int arr[] = {2, 3, 4, 5, 6, 7, 1};

  // int arr[] = {1, 4, 2, 3, 5};
  // int arr[] = {1, 2, 3, 4, 5, 6, 7};
  // int arr[] = {3, 4, 6, 1, 2, 5};

  // int size  = sizeof(arr)/sizeof(arr[0]);
  // display_array("Array", arr, size);
  // int min = rotated_minimum(arr, 0, (size - 1));
  // printf("\nMin[%d]: %d", min, arr[min]);
  // int max = rotated_maximum(arr, 0, (size - 1));
  // printf("\nMax[%d]: %d", max, arr[max]);
  //is_rotated_sorted(arr, size);
  // printf("\nIndex: %d", rotated_pivot(arr, 0, (size - 1)));
  // printf("\nRotated: %s", BOOL(is_rotated_sorted(arr, size)));
  return 0;
}
