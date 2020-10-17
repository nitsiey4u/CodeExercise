#include <cstdio>
#include <cstdlib>
#include <cstdbool>
#include <algorithm>

#define BOOL(val)  ((val) ? "True" : "False")

// Utility to display array
void print_array(const char* title, int* arr, int size) {
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

// Utility to compare values (True if left > right)
bool compare_values(int* left, int* right) {
	return (*left > *right);
}

// Utility to swap values
void swap_values(int* left, int* right) {
	//printf("\nSwapping %d <-> %d", *left, *right);
	int temp = *right;
	*right = *left;
	*left = temp;
}

// Bubble Sort Implementation - O(N2)
void bubble_sort(int* arr, const int size) {
  bool noexchange = true;
  for(int outer = 0; outer < size; outer++) {
		// Reduce size of array (one less than actual size)
    for(int inner = 0; inner < (size - outer - 1); inner++) {
			// Bubble largest value to end of array size
      if(arr[inner] > arr[inner + 1]) {
        noexchange = false;
        swap_values(&arr[inner], &arr[inner+1]);
      }
    }
    if (noexchange) {
      printf("\nArray already sorted");
      break;
    }
  }
}

// Insertion Sort Implementation - O(N2)
void insertion_sort(int* arr, const int size) {
  for(int outer = 1; outer < size; outer++) {
    int key = arr[outer];
    int inner = outer - 1;
		/* Move elements of arr[0..outer-1], that are
    greater than key, to one position ahead
    of their current position */
    while(inner >= 0 && arr[inner] > key) {
        arr[inner+1] = arr[inner];
        inner = inner - 1;
    }
    arr[inner + 1] = key;
  }
}

// Selection Sort Implementation - O(N2)
void selection_sort(int* arr, const int size) {
	int outer_idx, inner_idx;
	for (outer_idx = 0; outer_idx < size; outer_idx++) {
		// select first index as smallest index
		int select_idx = outer_idx;
		// compare selected element with all other elements
		for(inner_idx = (outer_idx+1); inner_idx < size; inner_idx++) {
			// change selected index
			if (arr[inner_idx] < arr[select_idx]) {
				select_idx = inner_idx;
			}
		}
		// swap with intial selected element with newly selected one
		int temp_value = arr[outer_idx];
		arr[outer_idx] = arr[select_idx];
		arr[select_idx] = temp_value;
	}
}

// Quick partition array
int quick_partition_array(int* arr, const int low, const int high) {
	int partition = low;
	int pivot = high;
	for(int index = low; index < high; index++) {
		if (arr[index] <= arr[pivot]) {
			swap_values(&arr[partition], &arr[index]);
			partition++;
		}
	}
	swap_values(&arr[partition], &arr[pivot]);
	return partition;
}

// Quick Sort Implementation - O(NLogN)
// Already sorted array: 1, 2, 3, 4, 5 - O(N2) worst case
void quick_sort(int* arr, const int low, const int high) {
	if(low < high) {
		int partition = quick_partition_array(arr, low, high);
		quick_sort(arr, low, (partition - 1));
		quick_sort(arr, (partition + 1), high);
	}
}

// Merge sort array
void merge_sort_array(int* arr, const int low, const int middle, const int high) {
	int lSize = (middle - low) + 1;
	int rSize = (high - middle);
	int left[lSize];
	int right[rSize];
	int l, r, index;

	// copy left array
	for(l=0, index=low; l < lSize; index++, l++)
		left[l] = arr[index];

	// copy right array
	for(r=0, index=(middle + 1); r < rSize; index++, r++)
		right[r] = arr[index];

	// merge elements in sorted order until one array is done
	for(index=low, l=0, r=0; ((l < lSize) && (r < rSize)); index++) {
		if(left[l] < right[r]) {
			arr[index] = left[l];
			l++;
		}
		else if(left[l] > right[r]) {
			arr[index] = right[r];
			r++;
		}
		else {
			arr[index] = left[l];
			l++;
			r++;
		}
	}
	// copy elements of left pending array
	while(l < lSize) {
		arr[index] = left[l];
		l++;
		index++;
	}
	// copy elements of right pending array
	while(r < rSize) {
		arr[index] = right[r];
		r++;
		index++;
	}
}

// Merge Sort Implementation - O(NLogN)
void merge_sort(int* arr, const int low, const int high) {
	if(low < high) {
		int median = low + (high - low) / 2;
		merge_sort(arr, low, median);
		merge_sort(arr, (median + 1), high);
		merge_sort_array(arr, low, median, high);
	}
}

// Get parent for specific index in heap - O(1)
int heap_parent(const int index) {
  return floor((index - 1)/ 2);
}

// Get left child for specific parent index in heap - O(1)
int heap_left(const int index) {
  return (index * 2) + 1;
}

// Get right child for specific parent index in heap - O(1)
int heap_right(const int index) {
  return (index * 2) + 2;
}

// Max heapify driver function for specific index - O(LogN)
void max_heapify(int* arr, const int index, const int heap) {
	int left = heap_left(index);
	int right = heap_right(index);
	int largest = index;
	//printf("\nParent: %d, Left: %d, Right: %d", index, left, right);
	if((left <= heap) && (arr[left] > arr[largest]))
		largest = left;
	if((right <= heap) && (arr[right] > arr[largest]))
		largest = right;
	if(largest != index){
		swap_values(&arr[index], &arr[largest]);
		max_heapify(arr, largest, heap);
	}
}

// Build max-heap helper function - O(N)
void build_max_heap(int* arr, const int heap) {
	for(int index=(heap/2); index >= 0; index --)
	 	max_heapify(arr, index, heap);
}

// Heap Sort Implementation - O(NLogN)
void heap_sort(int* arr, const int last) {
	int index, heap;
	// Build heap upto last element of array
	build_max_heap(arr, last);
	// Set heap to (last - 1) size (to exclude last element)
	// Iterate from last element of array upto 0th element
	for(index=last, heap=(last - 1); index > 0; index--, heap --) {
		swap_values(&arr[index], &arr[0]);
		max_heapify(arr, 0, heap);
	}
}

// Increase heap key - O(LogN)
void increase_heap_key(int* arr, int index, int newkey) {
  if(newkey < arr[index]) {
		// Newly added key is smaller than key at current index
    printf("\nNew key is smaller");
    return;
  }
  arr[index] = newkey;
	// Compare newly added key with its parent's key
  while((index > 0) && (arr[heap_parent(index)] < arr[index])) {
		// Newly added key is greater than parent's key, swap values
    swap_values(&arr[heap_parent(index)], &arr[index]);
		// Iterate upwards to repeat comparison for above swapped parent
    index = heap_parent(index);
  }
}

// Function to move 0 in binary array - O(N)
void move_zeros(int* arr, int size) {
	int counter, index;
	for(index=0, counter=0; index < size; index++) {
		if(arr[index] == 0) {
			swap_values(&arr[counter], &arr[index]);
			counter++;
		}
	}
	printf("\nNon-Zero values: %d", (size - counter));
}

// Check if array is ascending or descending sorted - O(N)
// Helpful for quick select (for avoiding worst case time complexity)
bool is_sorted(int arr[], const int last) {
	int index, prev, next;
	// Iterate upto second last element of array
	for(index = 0, prev = 0; index < last; index++) {
		// Get difference (next - current)
		next = arr[index + 1] - arr[index];
		// For descending, prev and next difference are both negative
		// For ascending, prev and next difference are both positive
		if(((prev <= 0) && (next <= 0)) ||
		 	 ((prev >= 0) && (next >= 0))) {
			// Set prev difference for further iteration
			prev = next;
		} else {
			// Prev and Next are mismatching positive/negative values
			return false;
		}
	}
	// Array is sorted
	return true;
}

// Quick Select Algorithm - O(N) average
// Return value of unsorted array at specified index (kpos)
// For sorted array: 1, 2, 3, 4, 5 - O(N2) worst case
// Before calling quick select ensure array is not sorted
int quick_select(int* arr, const int low, const int high, const int kpos) {
	// Ensure k position lies within the boundaries of low and high
	if((low <= kpos) && (kpos <= high)) {
		// Quick partition array and save current index
		int index = quick_partition_array(arr, low, high);
		// printf("\nValue: %d", arr[index]);
		if(index == kpos) {
			// Current index matches K
			return arr[index];
		} else if(kpos < index) {
			// If K position < Current Index, recurse left array
			return quick_select(arr, low, (index - 1), kpos);
		} else {
			// If Current Index < K position, recurse right array
			return quick_select(arr, (index + 1), high, kpos);
		}
	}
	return -1;
}

// Find K smallest element in unsorted array of distinct elements
// Using quick select algorithm - O(N)
int get_ksmallest(int* arr, const int size, const int kval) {
	int eIndex = size - 1;	// Last element index
	int kIndex = kval - 1;	// (K - 1) Smallest Index
	int result = quick_select(arr, 0, eIndex, kIndex);
	printf("\n%dth smallest value: %d", kval, result);
	return result;
}

// Find K largest element in unsorted array of distinct elements
// Using quick select algorithm - O(N)
int get_klargest(int* arr, const int size, const int kval) {
	int eIndex = size - 1;			// Last element index
	int kIndex = size - kval;		// (Size - K) Smallest Index
	int result = quick_select(arr, 0, eIndex, kIndex);
	printf("\n%dth largest value: %d", kval, result);
	return result;
}

// Find mean and median of unsorted array - O(N)
void mean_median(int* arr, const int size) {
	// Get mean using average of values - O(N)
	double mean = 0;
	for(int index = 0; index < size; index++) {
		mean = mean + arr[index];
	}
	printf("\nMean: %.2f", (mean / size));

	// Check for odd/even array size, to find middle element(s)
	double median = 0;
	const bool is_even 	= ((size % 2) == 0) ? true : false;
	// For odd array size, median is middle element
	// For even array size, median is average of middle elements
	const int mid_index = floor(size / 2);
	const int pre_index = (is_even) ? (mid_index - 1) : mid_index;

	// Check if array is already sorted
	if(is_sorted(arr, (size - 1))) {
		// Handling worst case of quick select algorithm - O(N2)
		median = ((double)arr[mid_index] + arr[pre_index]) / 2;
	} else {
	// Get mid_index partition using quick select algorithm - O(N)
		median = (double)quick_select(arr, 0, (size - 1), mid_index);
		if(is_even) {
			// All elements on left are smaller than above mid_index partition
			// Set upper limit to (mid_index - 1) to find pre_index partition
			median = median + quick_select(arr, 0, (mid_index - 1), pre_index);
			median = median / 2;
		}
	}
	printf("\nMedian: %.2f", median);
}

// Find ordered index of K in unsorted array with distinct elements
// Using quick paritition array - O(N)
void ordered_position(int* arr, const int size, const int kval) {
	int kval_index = -1;
	// Find original distinct position of K - O(N)
	for(int curr_index = 0; curr_index < size; curr_index ++) {
		// Ensure distinct occurence of K is found
		if(arr[curr_index] == kval) {
			if(kval_index < 0) {
				// Found first occurence of K
				kval_index = curr_index;
			} else {
				// Found multiple occurences of K
				kval_index = (kval_index > 0) ? -2 : (kval_index - 1);
			}
		}
	}
	// K does not exists or occurs more than once
	if(kval_index < 0) {
		// Functionality can be modified to handle reptitive elements
		printf("\nKvalue %d exists %d times. Cannot find ordered position",
						kval, (kval_index == -1) ? 0 : abs(kval_index));
		return;
	}

	// Swap K with last element of array as new pivot
	swap_values(&arr[kval_index], &arr[size - 1]);

	// Quick partition array - O(N)
	// K will be at partitioned sorted position between two halfs
	int sort_index = quick_partition_array(arr, 0, size - 1);
	// Define order of K
	if(sort_index <= floor(size/2)) {
		printf("\n%d is %d smallest element in sorted array",
					 kval, (sort_index + 1));
	} else {
		printf("\n%d is %d largest element in sorted array",
					 kval, (size - sort_index));
	}
}

// For unsorted array, find sorted neighbours of kval - O(N)
// Example: 3, 1, 2 (where n[3]: 2, n[2]: 1, n[2]: 1, 2)
void ordered_neighbours(int* arr, const int size, const int kval){
	int kval_index = -1;
	// Find original distinct position of K - O(N)
	for(int curr_index = 0; curr_index < size; curr_index ++) {
		// Ensure distinct occurence of K is found
		if(arr[curr_index] == kval) {
			if(kval_index < 0) {
				// Found first occurence of K
				kval_index = curr_index;
			} else {
				// Found multiple occurences of K
				kval_index = (kval_index > 0) ? -2 : (kval_index - 1);
			}
		}
	}
	// K does not exists or occurs more than once
	if(kval_index < 0) {
		printf("\nKvalue %d exists %d times. Cannot find neigbours",
						kval, (kval_index == -1) ? 0 : abs(kval_index));
		return;
	}

	// Swap K with last element of array as new pivot
	swap_values(&arr[kval_index], &arr[size - 1]);

	// Quick partition array - O(N)
	// K will be at partitioned sorted position between two halfs
	int sort_index = quick_partition_array(arr, 0, size - 1);
	// printf("\nPartitioned Index: %d Value: %d", partition, arr[partition]);
	// print_array("New Array", arr, size);

	// K element is at start, so only right neighbour exists
	if(sort_index == 0) {
		// Quick select to find only neighbour - O(N)
		int right_index = sort_index + 1;
		int right_value = quick_select(arr, 0, (size - 1), right_index);
		printf("\nSorted neighbour of %d is: %d ", kval, right_value);
	}
	// K element is at end, so only left neighbour exists
	else if(sort_index == (size - 1)) {
		// Quick select to find only neighbour - O(N)
		int left_index = sort_index - 1;
		int left_value = quick_select(arr, 0, (size - 1), left_index);
		printf("\nSorted neighbour of %d is: %d ", kval, left_value);
	}
	// K element is at middle, so both left and right neighbour exists
	else {
		// Quick select to find neighbour only in left half - O(N)
		int left_index = sort_index - 1;
		int left_value = quick_select(arr, 0, (sort_index - 1), left_index);
		// Quick select to find neighbour only in right half - O(N)
		int right_index = sort_index + 1;
		int right_value = quick_select(arr, (sort_index + 1), (size - 1), right_index);
		// Display neigbours
		printf("\nSorted neighbours of %d are: %d and %d",
					 kval, left_value, right_value);
	}
	// Question: After getting ordered position for K
	// Can we use local maxima(left half) and minima(right half)
	// Answer: Absolutely NO,
	// Any element can be local maxima in left half not neighbour of K
	// Any element can be local maxima in right half not neighbour of K
}

// Remove duplicate from sorted array (in-place) - O(N)
int remove_duplicates(int arr[], int size) {
 int high = size - 1;		// Last element of array
 int prev = 0;					// Position available to insert distinct element
 int next = 0;					// Pointer to last occurence of repetitive element
 // Iterate array upto second last element
 for(int index = 0; index < high; index++) {
	 // Check if current element is same as next elemet
   if(arr[index] == arr[index + 1]) {
		 // Next points to next repetitive element
     next = index + 1;
   } else {
		 // Swap last repetitive element with distinc element position
     swap_values(&arr[next], &arr[prev]);
		 // Increment pointer to elements
     prev++;
     next++;
   }
 }
 // For last element check if its processed and swap accordingly
 if((next > prev) && (next < size) && (arr[next] != arr[prev])) {
   swap_values(&arr[next], &arr[prev]);
   prev++;
 }
 // Return size of reduced array
 return (prev == 0) ? 1 : prev;
}

// Main driver function
int main(int argc, char* argv[]) {
	// int arr[] = {1, 3, 4, 2, 6, 5, 8, 7};
	// int size = (int)(sizeof(arr)/sizeof(arr[0]));
	// build_max_heap(arr, (size - 1));
	// print_array("Binary Heap", arr, size);

	// increase_heap_key(arr, (size - 1), 9);
	// print_array("Binary Heap2", arr, size);

	// int arr[] = {23, 11, 12, 8, 14, 19, 3, 32, 4, 20};
	// int arr[] = {1, 3, 4, 2, 6, 5, 8, 7};
	//print_array("Input Array", arr, size);

	// int arr[] = {1, 2, 3, 4, 5};
	// int arr[] = {5, 4, 6, 2, 7};
	// printf("Is sorted: %s", BOOL(is_sorted(arr, (size - 1))));

	// mean_median(arr, size);

	// int arr[] = {1, 3, 4, 2, 6, 5, 8, 7};
	// int size = (int)(sizeof(arr)/sizeof(arr[0]));
	//
	// ordered_position(arr, size, 1);
	// print_array("Input Array", arr, size);
	// ordered_neighbours(arr, size, 7);

	// get_ksmallest(arr, size, 1);
	// get_klargest(arr, size, 2);

	// heap_sort(arr, (size - 1));
	// print_array("Sorted Array", arr, size);

	// int index = binary_search_recursive(arr, 0, (size - 1), target);
	// printf("\nTarget: %d, index: %d", target, index);
	//
	// int* range = binary_search_range(arr, size, target);
	// printf("\nRange of %d is [%d, %d]", target, range[0], range[1]);
	// free(range);

	// quick_sort(arr, 0, (size - 1));
	// merge_sort(arr, 0, (size - 1));
	// heap_sort(arr, (size - 1));
	// print_array("Sorted Array", arr, size);
}
