#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>

using namespace std;

#define NIL_VALUE       -1
#define MAX_SIZE        20
#define SHOW_BOOL(x)   ((x)?"T":"F")
#define MAX(x,y)       ((x>y)?(x):(y))
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

// Helper to display array
void display_array(int arr[], int size) {
  printf("\nValue:");
  for(int index = 0; index < size; index++) {
    printf("\t%d", arr[index]);
  }
  printf("\nIndex:");
  for(int index = 0; index < size; index++) {
    printf("\t%d", index);
  }
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
void longest_increasing_subsequence(int arr[], int size) {
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
void display_string_matrix(string source, string target, int** matrix) {
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
void longest_common_subsequence(string source, string target) {
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
  // display_string_matrix(source, target, sublen_matrix);

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

// Minimum Edit Distance to edit source to target - O(MN)
void minimum_edit_distance(string source, string target) {
  int source_length = source.length() + 1;  // For Row - 0 (Null Char)
  int target_length = target.length() + 1;  // For Col - 0 (Null Char)
  // Allocate distance matrix
  int** distance_matrix = (int**)malloc(sizeof(int*) * source_length);
  for(int index = 0; index < source_length; index++) {
    distance_matrix[index] = (int*)malloc(sizeof(int) * target_length);
  }
  // Initialize distance matrix
  for(int row = 0; row < source_length; row++) {
    for(int col = 0; col < target_length; col++) {
      if(row == 0) {
        // To edit from NULL source to target char (by inserting target)
        // Moving Right -> Insert Operation
        distance_matrix[row][col] = col;
      } else if(col == 0) {
        // To edit from source char to NULL target (by removing source)
        // Moving Down ! Delete Operation
        distance_matrix[row][col] = row;
      } else {
        distance_matrix[row][col] = 0;
      }
    }
  }
  // Iterate over distance matrix
  for(int row = 1; row < source_length; row++) {
    for(int col = 1; col < target_length; col++) {
      int source_index = row - 1; // Set source string index
      int target_index = col - 1; // Set target string index
      if(source[source_index] == target[target_index]) {
        // Source = Target, copy value from diagonal (without adding cost)
        distance_matrix[row][col] = distance_matrix[row - 1][col - 1];
      } // End of if
      else {
        // Copy previous column (LEFT) element value
        int insert = distance_matrix[row][col - 1];
        // Copy previous row (ABOVE) element value
        int remove = distance_matrix[row - 1][col];
        // Copy previous row,col (DIAGONAL) element value
        int replace = distance_matrix[row - 1][col - 1];
        // Source != Target, get min from neighbours (left, diagnoal, above)
        int minval = min(insert, remove);
        // Get min value with diagonal element and add 1 transition cost
        distance_matrix[row][col] = min(minval,replace) + 1;
      } //  End of else
    } // End of inner for loop (target)
  } // End of outer for loop (source)

  // Display distance matrix
  display_string_matrix(target, source, distance_matrix);
  printf("\nSource: %s", source.c_str());
  printf("\nTarget: %s", target.c_str());

  // Backtracking to display result
  int row = source_length - 1;
  int col = target_length - 1;
  printf("\nMinimum edit distance: %d", distance_matrix[row][col]);
  while((row > 0) && (col > 0)) {
    int source_index = row - 1; // Set source string index
    int target_index = col - 1; // Set target string index
    if(source[source_index] == target[target_index]) {
      // The current value is coming from diagonal
      row = row - 1;
      col = col - 1;
    } else {
      int val = distance_matrix[row][col] - 1;
      if(val == distance_matrix[row - 1][col - 1]) {
        // The current value is coming from diagonal (replacement)
        row = row - 1;
        col = col - 1;
        printf("\nSource '%c' should be replaced by Target '%c'",
                source[source_index], target[target_index]);
      } else if (val == distance_matrix[row][col - 1]) {
        // The current value is coming from previous (insertion)
        col = col - 1;
        printf("\nTarget '%c' should be inserted", target[target_index]);
      } else {
        // The current value is coming from above (deletion)
        row = row - 1;
        printf("\nSource '%c' should be removed", source[source_index]);
      }
    }
  } // End of while loop

  // Handle remaining indices
  if((row == 0) && (col > 0)) {
    // Target needs to be inserted
    printf("\nTarget '%c' should be inserted", target[col - 1]);
  } else if((col == 0) && (row > 0)) {
    // Source needs to be deleted
    printf("\nSource '%c' should be removed", source[row - 1]);
  } else {
    // Processing completed do nothing
  }

  // Deallocate distance matrix
  for(int index = 0; index < source_length; index++) {
    free(distance_matrix[index]);
  }
  free(distance_matrix);
}

// Find length of longest palindromic subsequence - O(N2)
int longest_palindromic_subsequence(string str, int low, int high, int** seq) {
  // 1-character is palindrome
  if((low == high) || (seq[low][high] != -1)) {
    return seq[low][high];
  }

  if((str[low] == str[high]) && ((low + 1) == high)) {
      // 2-character palindrome for matching first and last chars
    seq[low][high] = 2;
  } else if(str[low] == str[high]) {
    // N-character palindrome for matching first and last chars
    seq[low][high] = 2 + longest_palindromic_subsequence(str, low + 1, high - 1, seq);
  } else {
    // Recurse to find another palindrome
    seq[low][high] = max(longest_palindromic_subsequence(str, low + 1, high, seq),
                         longest_palindromic_subsequence(str, low, high - 1, seq));
  }
  return seq[low][high];
}

// Reverse input string - O(N)
void reverse_string(string & str) {
  int length = str.length() - 1;
  for(int index = 0; index < (length/2); index++) {
    swap(str[index], str[length - index]);
  }
}

// Find longest palindromic subsequence - O(N2)
void palindromic_subsequence(string str) {
  int length = str.length();
  // Allocate DP matrix
  int** seq = (int**) malloc(sizeof(int*) * length);
  for(int index = 0; index < length; index++) {
    seq[index] = (int*) malloc(sizeof(int) * length);
  }
  // Initialize DP matrix
  for(int row = 0; row < length; row++) {
    for(int col = 0; col < length; col++) {
      seq[row][col] = (row == col) ? 1 : -1;
    }
  }
  // Get length of longest palindromic subsequence
  int val = longest_palindromic_subsequence(str, 0, (str.length() - 1), seq);
  printf("\nLength: %d", val);
  // Deallocate DP matrix
  for(int index = 0; index < length; index++) {
    free(seq[index]);
  }
  free(seq);

  // Get longest palindromic subsequence
  string source = str;    // Original string
  string target = str;    // Reversed string
  reverse_string(target);
  // Find LCS to get palindomic subsequence - O(N2)
  longest_common_subsequence(source, target);
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

struct KnapSack{
  int value;
  int weight;
};
typedef struct KnapSack KNAPSACK;

// Find subset of items with sum weights < knapsack weight with max value
//  Time complexity - O(NW) N: Number of items, W: Weight of Knapsack
int knapsack_maximum(KNAPSACK snap[], int values[], int indices[],
                     int size, int weight) {
  // Very important - as size of array is +1 than actual index
  int index = size - 1;

  // All weight is either used up or no items remaining
  if((weight == 0)||(index < 0)) {
    return 0;
  }

  // Check if max val is already calculated
  if(values[index] != -1) {
    // Negative value used as lowest value is 0
    return values[index];
  }

  // Check if current item > weight
  if(snap[index].weight > weight) {
    // Exclude this item (as its heavier)
    // Save maximum value for next iteration
    values[index] = knapsack_maximum(snap, values, indices, (size - 1), weight);
    indices[index] = indices[index - 1];
  } else {
    // Include this item (as its ligher), value can be low/high
    int inwgt = weight - snap[index].weight;
    int inval = snap[index].value +
                knapsack_maximum(snap, values, indices, (size - 1), inwgt);

    // Exclude this item (as its ligher), value can be low/high
    int exval = knapsack_maximum(snap, values, indices, (size - 1), weight);

    // Save maximum value for next iteration
    if(inval > exval) {
      values[index]  = inval;
      indices[index] = index;
    } else {
      values[index]  = exval;
      indices[index] = indices[index - 1];
    }
  }
  return values[index];
}

// Remove duplicate from array (in-place) - O(N)
int remove_duplicates(int arr[], int size) {
 int prev = 0;
 int next = 0;
 for(int index = 0; index < (size - 1); index++) {
   if(arr[index] == arr[index + 1]) {
     next = index + 1;
   } else {
     swap(arr[next], arr[prev]);
     prev++;
     next++;
   }
 }
 if((next > prev) && (next < size) && (arr[next] != arr[prev])) {
   swap(arr[next], arr[prev]);
   prev++;
 }
 return (prev == 0) ? 1 : prev;
}

// Driver program for knapsack problem
void knapsack_driver(int arrWeights[], int arrValues[], int size, int weight) {
  KNAPSACK snap[size];
  int values[size];
  int indices[size];
  // Init arrays
  for(int index = 0; index < size; index++) {
    snap[index].weight = arrWeights[index];
    snap[index].value  = arrValues[index];
    values[index]  = -1;
    indices[index] = -1;
  }
  // Get maximum subset value
  int maxval = knapsack_maximum(snap, values, indices, size, weight);
  printf("\nKnapsack Maximum: %d", maxval);
  // Remove repetitive items from indices - O(N)
  int maxidx = remove_duplicates(indices, size);
  int maxwgt = weight;
  // Display subset items (reverse way)
  for(int index = (maxidx - 1); index >= 0; index--) {
    if(maxwgt >= 0) {
      int item = indices[index];
      printf("\nItem: %d (Value: %d, Weight: %d)",
             item, snap[item].value, snap[item].weight);
      maxwgt = maxwgt - snap[item].weight;
    }
  } // End of for loop
}

// Time complexity - O(NM)  N: Number of steps M: Max steps at time
// F(N) = F(N-1) + F(N-2) + F(N-3) for M=3
int staircase_steps(int* steps, const int number, const int maxopt) {
  if(number <= 1) {
    // Initialized arr[0] = arr[1] = 1
    return ((number == 0)||(number == 1)) ? steps[number] : 0;
  }
  if(steps[number] == 0) {
    for(int index = 1; index <= maxopt; index++) {
      steps[number] += staircase_steps(steps, (number - index), maxopt);
    }
  }
  return steps[number];
}

// Recursive function for non-contiguous subarray max sum
int contiguous_sum(int arr[], int sum[], int high, int index, int & maxval) {
  if((0 <= index) && (index <= high)) {
    if(sum[index] != 0) {
      return sum[index];
    }
    if(high == 0) {
      sum[index] = arr[0];
    } else {
      int prev_max = contiguous_sum(arr, sum, high, (index - 1), maxval);
      sum[index] = max((prev_max + arr[index]), arr[index]);
      maxval = max(maxval, sum[index]);
    }
    return sum[index];
  }
  return -1;
}

// Recursive function for non-contiguous subarray max sum
int noncontiguous_sum(int arr[], int sum[], int high, int index) {
  if((0 <= index) && (index <= high)) {
    if(sum[index] != 0) {
      return sum[index];
    }
    if(high == 0) {
      sum[index] = arr[0];
    } else if(high == 1) {
      sum[index] = max(arr[0], arr[1]);
    } else {
      sum[index] = max(noncontiguous_sum(arr, sum, high, (index - 2)) + arr[index],
                       noncontiguous_sum(arr, sum , high, (index - 1)));
    }
    return sum[index];
  }
  return 0;
}

// Get maximum sum of non-contiguous subarray - O(N)
// Kadane's algorithm for subarray max sum
void maxsum_subarray(int arr[], int size, bool contiguous) {
  int sum[size];
  for(int index = 0; index < size; index++) {
    sum[index] = 0;
  }
  printf("\nInput Array: ");
  display_array(arr, size);
  if(contiguous) {
    int maxsum = INT_MIN;
    int maxval = contiguous_sum(arr, sum, size, (size - 1), maxsum);
    printf("\nContiguous SubArray Max Sum: %d", maxsum);
  } else {
    int maxsum = noncontiguous_sum(arr, sum, size, (size - 1));
    printf("\nNon-Contiguous SubArray Max Sum: %d", maxsum);
  }
  printf("\nMaxSum Array: ");
  display_array(sum, size);
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
  // longest_increasing_subsequence(arr, size);

  // longest_common_subsequence("bqdrcvefgh", "abcvdefgh");
  // longest_common_subsequence("ABCDGH","AEDFHR");

  // minimum_edit_distance("adceg", "abcfg");

  // int arr[] = {3, 8, 4, 12, 5, 2};
  // int arr[] = {3, 34, 4, 12, 5, 2, 1, 1};
  // int size = sizeof(arr)/sizeof(arr[0]);
  // find_subset_sum(arr, size, 11);

  // int number = 7;
  // int maxopt = 3;
  // int* steps = (int*) malloc((sizeof(int) * (number + 1)));
  // for(int index = 0; index <= number; index++) {
  //   steps[index] = (index <= 1) ? 1 : 0;
  // }
  // int ways = staircase_steps(steps, number, maxopt);
  // printf("\nWays to reach %dth step (max %d): %d", number, maxopt, ways);
  // free(steps);
  //

  // int seq[length];
  // for(int index = 0; index < length; index++) {
  //   seq[index] = 0;
  // }
  // int val = longest_palindrome_length(str, 0, str.length() - 1, seq);
  // printf("\nLength: %d", val);
  //
  // for(int index = 0; index < length; index++) {
  //   printf("\n[%d]: %d", index, seq[index]);
  // }

  // palindromic_subsequence("GEEKSFORGEEKS");

  // int arr[] = {-2, 1, 0, -3, 2, 4, 9, -1, -2, 1, 5, -3};
  // int size = sizeof(arr)/sizeof(arr[0]);
  // maxsum_subarray(arr, size, true);

  // int arr[] = { -8, -3, -6, -2, -5, -4 };
  // int size  = sizeof(arr)/sizeof(arr[0]);
  // maxsum_subarray(arr, size, true);

  // int arr[] = {1,2,3,8,10,1};
  // int size = sizeof(arr)/sizeof(arr[0]);
  // maxsum_subarray(arr, size, false);
  return 0;
}
