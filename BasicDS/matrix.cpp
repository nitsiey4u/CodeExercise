#include "stdio.h"
#include "stdlib.h"

#define MAX_ROWS 5
#define MAX_COLS 4
#define MAX_DIRS 4

// Input matrix (static)
int arr[MAX_ROWS][MAX_COLS] = {
  {2, 4, 6, 8},
  {5, 9, 12, 16},
  {9, 5, 11, 2},
  {2, 11, 5, 9},
  {3, 2, 1, 8},
};

// Utility to dynamically allocated matrix
void dynamic_alloc(int** arr) {
  int i;
  arr = (int **) malloc(sizeof(int *) * MAX_ROWS);
  for(i = 0; i < MAX_ROWS; i++) {
    arr[i] = (int*) malloc(sizeof(int) * sizeof(MAX_COLS));
  }
}

// Utility to free allocated matrix
void free_alloc(int** arr) {
  int i;
  for(i = 0; i < MAX_ROWS; i++)
    free(arr[i]);
  free(arr);
}

// Utility to display matrix
void print_matrix(int arr[][MAX_COLS], int rows, int cols) {
  int i, j;
  printf("\nMatrix: \n");
  for(i=0; i < rows; i++) {
    for(j=0; j < cols; j++) {
      printf("\t%d", arr[i][j]);
    }
    printf("\n");
  }
}

// Spiral Matrix Display Implementation
void spiral_print(int arr[][MAX_COLS], int rows, int cols) {
  int cur_dir = 0;
  int top_row = 0;
  int bottom_row = (rows - 1);
  int left_col = 0;
  int right_col = (cols - 1);
  printf("\nSpiral Print: ");
  while((top_row <= bottom_row) && (left_col <= right_col)) {
    int row_index, col_index;

    if(cur_dir == 0) {
      row_index = top_row;
      for(col_index = left_col; col_index <= right_col; col_index++)
        printf("\t%d", arr[row_index][col_index]);
      top_row ++;
    }

    if(cur_dir == 1) {
      col_index = right_col;
      for(row_index = top_row; row_index <= bottom_row; row_index++)
        printf("\t%d", arr[row_index][col_index]);
      right_col --;
    }

    if(cur_dir == 2) {
      row_index = bottom_row;
      for(col_index = right_col; col_index >= left_col; col_index--)
        printf("\t%d", arr[row_index][col_index]);
      bottom_row --;
    }

    if(cur_dir == 3) {
      col_index = left_col;
      for(row_index = bottom_row; row_index >= top_row; row_index--)
        printf("\t%d", arr[row_index][col_index]);
      left_col ++;
    }
    cur_dir = (cur_dir + 1) % MAX_DIRS;
  }
}

// Diagonal Matrix Display Implementation
void diagonal_print(int arr[][MAX_COLS], int rows, int cols) {
  int min_row = 0;
  int max_row = (rows - 1);
  int min_col = 0;
  int max_col = (cols - 1);
  int row_index, col_index;
  printf("\nDiagonal Print: \n");
  for(col_index=min_col, row_index=min_row; row_index <= (max_row - 1); row_index++){
    int row, col;
    for(row = row_index, col = col_index; (row >= min_row) && (col <= max_col); row--, col++)
      printf("\t%d", arr[row][col]);
    printf("\n");
  }
  for(row_index=max_row, col_index=min_col; col_index <= max_col; col_index++){
    int row, col;
    for(row = row_index, col = col_index; (row >= min_row) && (col <= max_col); row--, col++)
      printf("\t%d", arr[row][col]);
    printf("\n");
  }
}

// ZigZag Matrix Display Implementation
void zigzag_print(int arr[][MAX_COLS], int rows, int cols) {
  int row_index, col_index;
  int max_rows = (rows - 1);
  int max_cols = (cols - 1);
  printf("\nZigzag Print: \n");
  for(row_index = 0; row_index <= max_rows; row_index++) {
    if(row_index % 2 == 0) {
      for(col_index = 0; col_index <= max_cols; col_index++)
          printf("\t%d", arr[row_index][col_index]);
    }
    else {
      for(col_index = max_cols; col_index >= 0; col_index--)
          printf("\t%d", arr[row_index][col_index]);
    }
    printf("\n");
  }
}

// Main driver function
int main(int argc, char* argv[]) {
  print_matrix(arr, MAX_ROWS, MAX_COLS);
  //spiral_print(arr, MAX_ROWS, MAX_COLS);
  zigzag_print(arr, MAX_ROWS, MAX_COLS);
  return 0;
}
