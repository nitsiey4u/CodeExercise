#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

// Utility to display array
void print_array(const char* title, int* arr, int size) {
	int index;
	printf("\n%s: ", title);
	for(index = 0; index < size; index++) {
		printf(" %d ", arr[index]);
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

// Function to move 0 in binary array
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
int binary_search_recursive(int* arr, int low, int high, int target) {
	if (low <= high) {
		int mid = low + (high - low) / 2;
		if(arr[mid] == target)
			return mid;
		else if(arr[mid] < target)
			return binary_search_recursive(arr, (mid + 1), high, target);
		else
			return binary_search_recursive(arr, low, (mid - 1), target);
	}
	return -1;
}

// Find first index of number using binary search (iterative)
int binary_search_first_iterative(int* arr, int low, int high, int size, int target) {
	int low = 0;
	int high = (size - 1);
	while (low <= high) {
		int mid = low + ((high - low) >> 1);
		// check if previous index is different from target
		// boundary check for first index of array
		if(((mid == 0)||(arr[mid-1] < target)) && (arr[mid] == target))
			return mid;
		else {
			// process only right part, as we processed left part already
			if(arr[mid] < target)
				low = mid + 1;
			else
				high = mid - 1;
		}
	}
}

// Find last index of number using binary search (iterative)
int binary_search_last_iterative(int* arr, int low, int high, int size, int target) {
	int low = 0;
	int high = (size - 1);
	while (low <= high) {
		int mid = low + ((high - low) >> 1);
		// check if next index is different from target
		// boundary check for last index of array
		if(((mid == high)||(target < arr[mid+1])) && (arr[mid] == target))
			return mid;
		else {
			// process only left part, as we processed right part already
			if(target < arr[mid])
				high = mid - 1;
			else
				low = mid + 1;
		}
	}
}

// Find first index of number using binary search (recursive)
int binary_search_first_recursive(int* arr, int low, int high, int size, int target) {
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
int binary_search_last_recursive(int* arr, int low, int high, int size, int target) {
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
int* binary_search_range(int* arr, int size, int target) {
	int* range = (int*)malloc(sizeof(int) * 2);
	range[0] = binary_search_first_recursive(arr, 0, (size - 1), (size - 1), target);
	range[1] = (range[0] == -1) ? -1 : binary_search_last_recursive(arr, 0, (size - 1), (size - 1), target);
	return range;
}

// Bubble Sort Implementation
void bubble_sort(int* arr, int size) {
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

// Insertion Sort Implementation
void insertion_sort(int* arr, int size) {
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

// Selection Sort Implementation
void selection_sort(int* arr, int size) {
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

// Quick partition helper function
int quick_sort_partition(int* arr, int low, int high) {
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

// Quick Sort Implementation
void quick_sort_array(int* arr, int low, int high) {
	if(low < high) {
		int partition = quick_sort_partition(arr, low, high);
		quick_sort_array(arr, low, (partition - 1));
		quick_sort_array(arr, (partition + 1), high);
	}
}

// Merge array helper function
void merge_array_elements(int* arr, int low, int middle, int high) {
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

// Merge Sort Implementation
void merge_sort_array(int* arr, int low, int high) {
	if(low < high) {
		int median = low + (high - low) / 2;
		merge_sort_array(arr, low, median);
		merge_sort_array(arr, (median + 1), high);
		merge_array_elements(arr, low, median, high);
	}
}

// Max heapify helper function on specific index
void max_heapify(int* arr, const int index, const int heap) {
	int left = (index * 2) + 1;
	int right = left + 1;
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

// Build max-heap helper function
void build_max_heap(int* arr, int heap) {
	for(int index=(heap/2); index >= 0; index --)
	 	max_heapify(arr, index, heap);
}

// Heap Sort Implementation
void heap_sort(int* arr, int size) {
	int index, heap;
	build_max_heap(arr, size);
	for(index=size, heap=(size - 1); index > 0; index--, heap --) {
		swap_values(&arr[index], &arr[0]);
		max_heapify(arr, 0, heap);
	}
}

// Get parent for specific index in heap data-structure
int heap_parent(const int index) {
  return floor((index - 1)/ 2);
}

// Increase heap key
void increase_heap_key(int* arr, int index, int newkey) {
  if(newkey < arr[index]) {
    printf("\nNew key is smaller");
    return;
  }
  arr[index] = newkey;
  while((index > 0) && (arr[heap_parent(index)] < arr[index])) {
    swap_values(&arr[heap_parent(index)], &arr[index]);
    index = heap_parent(index);
  }
}

// Main driver function
int main(int argc, char* argv[]) {
	int arr[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
	int size = (int)(sizeof(arr)/sizeof(arr[0]));
	print_array("Input Array", arr, size);

	// int index = binary_search_recursive(arr, 0, (size - 1), target);
	// printf("\nTarget: %d, index: %d", target, index);
	//
	// int* range = binary_search_range(arr, size, target);
	// printf("\nRange of %d is [%d, %d]", target, range[0], range[1]);
	// free(range);

	// quick_sort_array(arr, 0, (size - 1));
	// merge_sort_array(arr, 0, (size - 1));
	// heap_sort(arr, (size - 1));
	print_array("Sorted Array", arr, size);
}
