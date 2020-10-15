#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>

using namespace std;

#define NIL_VALUE       -1
#define MAX_SIZE        20
#define SHOW_BOOL(x)   ((x)?"T":"F")
int lookup[MAX_SIZE];

/*
Links to Check:
https://www.geeksforgeeks.org/maximum-size-rectangle-binary-sub-matrix-1s/
https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/
*/

// Helper for qSort Comparator
int comparator(const void* a, const void *b) {
  return (*(int*)a - *(int*)b);
}

// Helper to display lookup table
void display_lookup() {
  printf("\nLookup Table: ");
  printf("\nValue: ");
  for(int index = 0; index < MAX_SIZE; index++) {
    printf("\t%d", lookup[index]);
  }
  printf("\nIndex: ");
  for(int index = 0; index < MAX_SIZE; index++) {
    printf("\t%d", index);
  }
}

// Recursively calculate fibonnaci value
int fib_recursion(int number) {
  if(number <= 1) {
    return number;
  }
  return fib_recursion(number - 1) +
         fib_recursion(number - 2);
}

// Dynamic programming fibonnaci using memoization
int fib_memoization(int number) {
  if(lookup[number] == -1) {
    lookup[number] = fib_memoization(number - 1) +
                     fib_memoization(number - 2);
  }
  return lookup[number];
}

// Find longest sequence of increasing numbers - O(N2)
void longest_increasing_subsubsequence(int arr[], int size) {
  int max_length = 1;
  int max_index  = 0;
  int sub_length[size];
  int sub_sequence[size];
  for(int index = 0; index < size; index++) {
    sub_length[index] = 1;
    sub_sequence[index] = 0;
  }
  // Outer loop over integer values
  int nextIndex, prevIndex;
  for(nextIndex = 1; nextIndex < size; nextIndex++) {
    // Inner loop over comparison integer values
    for(prevIndex = 0; prevIndex < nextIndex; prevIndex++) {
      // Left Value < Right Value
      if(arr[prevIndex] < arr[nextIndex]) {
        // Existing max sublength for nextIndex
        int old_length = sub_length[nextIndex];
        // To be updated new max sublength for nextIndex
        int new_length = sub_length[prevIndex] + 1;
        // If old length <= new length
        if(old_length <= new_length) {
          // Update with new max length
          sub_length[nextIndex] = new_length;
          // Save reference to prevIndex
          sub_sequence[nextIndex] = prevIndex;
          // Compare with maximum sub length value
          if(max_length <= new_length) {
            max_length = new_length;
            max_index  = nextIndex;
          }
        }
      }
    }
  }
  int position, counter;
  int result[max_length];
  for(position = max_index, counter = max_length; (position >=0) && (counter > 0);
      position = sub_sequence[position], counter--) {
    result[counter - 1] = arr[position];
  }
  //
  printf("\nIndex:");
  for(int index = 0; index < size; index++) {
    printf("\t%d", index);
  }
  printf("\nValue:");
  for(int index = 0; index < size; index++) {
    printf("\t%d", arr[index]);
  }
  // printf("\nLength:");
  // for(int index = 0; index < size; index++) {
  //   printf("\t%d", sub_length[index]);
  // }
  // printf("\nSubSeq:");
  // for(int index = 0; index < size; index++) {
  //   printf("\t%d", sub_sequence[index]);
  // }
  printf("\nResult:");
  for(int index = 0; index < max_length; index++) {
    printf("\t%d", result[index]);
  }
  printf("\nMax Length: %d", max_length);
}

// Helper display subsequence matrix
void display_subsequence_matrix(string source, string target, int** matrix) {
  int source_length = source.length() + 1; // For 0th column
  int target_length = target.length() + 1; // For 0th row
  printf("\nSubsequence Matrix:\n\t");
  for(int col = 0; col < source_length; col++) {
    if(col == 0) {
      printf("\t");
    } else {
      printf("\t%c", source[col - 1]);
    }
  }
  for(int row = 0; row < target_length; row++) {
    printf("\n");
    for(int col = 0; col < source_length; col++) {
      if(col == 0) {
        if(row == 0) {
          printf("\t  ");
        } else {
          printf("\t%c", target[row - 1]);
        }
      }
      printf("\t%d", matrix[row][col]);
    }
  }
}

// Find Longest Common Sub-sequence (LCS) of two strings - O(MN)
void longest_common_subsubsequence(string source, string target) {
  int source_length = source.length() + 1; // For 0th column
  int target_length = target.length() + 1; // For 0th row

  // Allocate subsequence length matrix
  int** sublen_matrix = (int**)malloc(sizeof(int*) * target_length);
  for(int index = 0; index < target_length; index++) {
    sublen_matrix[index] = (int*)malloc(sizeof(int) * source_length);
  }

  // 0th Column and 0th row is intialized as zero
  for(int row = 0; row < target_length; row++) {
    for(int col = 0; col < source_length; col++) {
      sublen_matrix[row][col] = 0;
    }
  }

  // Outer loop over target string - ROWS
  for(int row = 1; row < target_length; row++) {
    // Inner loop over source string - COLUMNS
    for(int col = 1; col < source_length; col++) {
      // Compare characters of string at row, col index
      if(target[row - 1] == source[col - 1]) {
        // Character match, increment value from left top diagonal
        sublen_matrix[row][col] = sublen_matrix[row-1][col-1] + 1;
      } else {
        // Character mismatch, take MAX(previous row, previous column)
        sublen_matrix[row][col] =
        max(sublen_matrix[row-1][col], sublen_matrix[row][col-1]);
      }
    }
  }

  // Display subsequence length matrix
  // display_subsequence_matrix(source, target, sublen_matrix);

  // Traverse bottom up for longest common subsequence
  int row = target_length - 1;
  int col = source_length - 1;
  int len = sublen_matrix[row][col];
  int pos = len - 1;
  char LCS[len + 1];
  LCS[len] = '\0';
  while((row > 0) && (col > 0) && (pos >=0)) {
    // If characters are same, go diagonally left upwards
    if(target[row - 1] == source[col - 1]) {
      LCS[pos] = source[col - 1];
      row --;
      col --;
      pos --;
    } else {
      // If characters are same, move left or above
      if(sublen_matrix[row - 1][col] > sublen_matrix[row][col - 1]) {
        // previous row
        row --;
      } else {
        // previous column
        col --;
      }
    }
  }
  printf("\nSource: %s", source.c_str());
  printf("\nTarget: %s", target.c_str());
  printf("\nLongest subsequence: %s (Length: %d)", LCS, len);

  // Deallocate subsequence length matrix
  for(int index = 0; index < target_length; index++) {
    free(sublen_matrix[index]);
  }
  free(sublen_matrix);
}

// Helper for displaying subset sum matrix
void display_subsetsum_matrix(int arr[], bool** matrix, const int rows, const int cols) {
  printf("\nSubset Sum Matrix:\n\t");
  for(int col = 0; col < cols ; col++) {
    printf("\t%d", col);
  }
  for(int row = 0; row < rows; row++) {
    printf("\n\t%d", ((row == 0) ? 0 : arr[row - 1]));
    for(int col = 0; col < cols ; col++) {
      printf("\t%s", SHOW_BOOL(matrix[row][col]));
    }
  }
  printf("\n");
}

// Find set of integers adding upto sum value - O(sum * N)
void find_subset_sum(int arr[], const int size, const int total) {
  // sort input array of values - O(NLogN)
  qsort(arr, size, sizeof(int), comparator);
  // Array of integers - ROW
  const int row_count = size + 1;
  int* val = (int*)malloc(sizeof(int) * row_count);
  for(int index = 0; index < row_count; index++) {
    val[index] = (index == 0)? 0 : arr[index - 1];
  }
  // Array of sum values - COLUMN
  const int col_count = total + 1;
  // Initialize sum array of values upto total
  int* sum = (int*)malloc(sizeof(int) * col_count);
  for(int index = 0; index < col_count; index++) {
    sum[index] = index;
  }
  // Initialize subset sum matrix (array_values x sum_values)
  bool** subset_matrix = (bool**)malloc(sizeof(bool*) * row_count);
  for(int index = 0; index < row_count; index++) {
    subset_matrix[index] = (bool*)malloc(sizeof(bool) * col_count);
  }
  // Initialize all rows and columns in subset sum matrix
  for(int row = 0; row < row_count; row++) {
    for(int col = 0; col < col_count; col++) {
      // Only column 0 is set to true, everything else false
      subset_matrix[row][col] = (col == 0);
    }
  }
  // Matrix top left corner (0,0) is also set to true
  subset_matrix[0][0] = true;

  // // Display subset sum matrix
  // display_subsetsum_matrix(arr, subset_matrix, row_count, col_count);

  // Fill sub set sum matrix with truth table
  for(int row = 1; row < row_count; row++) {
    for(int col = 1; col < col_count; col++) {
      // Compare array value and sum value
      if(val[row] == sum[col]) {
        // If array value = sum value, mark as true
        subset_matrix[row][col] = true;
      } else if(val[row] > sum[col]) {
        // If array value > sum value, copy value from above row
        subset_matrix[row][col] = subset_matrix[row-1][col];
      } else {
        // If array value < sum value
        if(subset_matrix[row-1][col]) {
          // If above row value is true, copy that value
          subset_matrix[row][col] = subset_matrix[row-1][col];
        } else {
          // Go to above row and use diff value as column index
          const int diff = sum[col] - val[row];
          subset_matrix[row][col] = subset_matrix[row-1][diff];
        }
      }
    } // End of inner loop
  } // End of outer loop

  // // Display subset sum matrix
  // display_subsetsum_matrix(arr, subset_matrix, row_count, col_count);

  // Display input numbers and possible set of values
  printf("\nArray:");
  for(int index = 0; index < size; index++) {
    printf("\t%d", arr[index]);
  }
  printf("\nExpected sum: %d", total);
  // Check bottom right last value for solution possibility
  if(subset_matrix[row_count - 1][col_count - 1] == true) {
    printf("\nAvailable set:");
    int row = row_count - 1;
    int col = col_count - 1;
    int counter = total;
    while((0 <= row) && (0 <= col) && (0 < counter)) {
      // Current value is true
      if(subset_matrix[row][col]) {
        // Check above row value
        if(subset_matrix[row - 1][col]) {
          // Above row value is true, so traverse to above row
          row = row - 1;
        } else {
          // Above row value is false, current row is part of set
          int intval = val[row];
          printf("\t%d", intval);
          // Traverse to above row
          row = row - 1;
          // Traverse to difference column
          counter = counter - intval;
          col = counter;
        }
      }
    }
  } else {
    printf("\nSum does not exist in given set of numbers.");
  }

  //  Deallocate subset matrix and related arrays
  for(int index = 0; index < row_count; index++) {
    free(subset_matrix[index]);
  }
  free(subset_matrix);
  free(val);
  free(sum);
}

int main() {
  // memset(lookup, -1, sizeof(lookup));
  // lookup[0] = 0;
  // lookup[1] = 1;
  // printf("\nResult: %d", fib_memoization(10));
  // display_lookup();
  // printf("\nResult: %d", fib_memoization(7));

  // int arr[] = {0, 4, 12, 2, 10, 6, 9, 13, 3, 11, 7, 15};
  // int arr[] = {50, 3, 10, 7, 40, 80};
  // int size = sizeof(arr)/sizeof(int);
  // longest_increasing_subsubsequence(arr, size);

  // longest_common_subsubsequence("bqdrcvefgh", "abcvdefgh");
  // longest_common_subsubsequence("ABCDGH","AEDFHR");

  // int arr[] = {3, 8, 4, 12, 5, 2};
  // int arr[] = {3, 34, 4, 12, 5, 2, 1, 1};
  // int size = sizeof(arr)/sizeof(arr[0]);
  // find_subset_sum(arr, size, 11);
  return 0;
}
