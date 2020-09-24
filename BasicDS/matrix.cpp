/***********************************************/
/********   Matrix Related Problems   **********/
/***********************************************/
#include "stdio.h"
#include "stdlib.h"

// Matrix for diagonal, spiral printing
#define MAX_ROWS 5    // Matrix 5 x 4
#define MAX_COLS 4    // Matrix 5 x 4

// Square matrix for add/subtract/multiply operations
#define TBL_ROWS 3    // Square Matrix 3 x 3
#define TBL_COLS 3    // Square Matrix 3 x 3

// Binary matrix for island counting - 8 neighbours
#define BIN_ROWS 5    // Matrix 5 x 5
#define BIN_COLS 5    // Matrix 5 x 5

// Color coded matrix for flood fill - 4 neighbours
#define CLR_ROWS 8
#define CLR_COLS 8

#define MAX_DIRS 4

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
  printf("\nNon-Square Matrix: \n");
  for(i=0; i < rows; i++) {
    for(j=0; j < cols; j++) {
      printf("\t%d", arr[i][j]);
    }
    printf("\n");
  }
}

// Transpose of matrix
void matrix_transpose(int mat[MAX_ROWS][MAX_COLS], int rows, int cols) {
  // Swap col count and row count, along with index values
  int res[cols][rows];
  for(int rowIndex = 0; rowIndex < rows; rowIndex++) {
    for(int colIndex = 0; colIndex < cols; colIndex++) {
      res[colIndex][rowIndex] = mat[rowIndex][colIndex];
    }
  }
  // Display tranposed matrix
  printf("\nTranspose Matrix");
  for(int rowIndex = 0; rowIndex < cols; rowIndex++) {
    printf("\n");
    for(int colIndex = 0; colIndex < rows; colIndex++) {
      printf("\t%d", res[rowIndex][colIndex]);
    }
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
  // Spiral traversal
  while((top_row <= bottom_row) && (left_col <= right_col)) {
    int row_index, col_index;
    // Right Traverse >
    if(cur_dir == 0) {
      row_index = top_row;
      for(col_index = left_col; col_index <= right_col; col_index++)
        printf("\t%d", arr[row_index][col_index]);
      top_row ++;
    }
    // Down Traverse v
    if(cur_dir == 1) {
      col_index = right_col;
      for(row_index = top_row; row_index <= bottom_row; row_index++)
        printf("\t%d", arr[row_index][col_index]);
      right_col --;
    }
    // Left Traverse <
    if(cur_dir == 2) {
      row_index = bottom_row;
      for(col_index = right_col; col_index >= left_col; col_index--)
        printf("\t%d", arr[row_index][col_index]);
      bottom_row --;
    }
    // Top Traverse ^
    if(cur_dir == 3) {
      col_index = left_col;
      for(row_index = bottom_row; row_index >= top_row; row_index--)
        printf("\t%d", arr[row_index][col_index]);
      left_col ++;
    }
    // Change traversal direction
    cur_dir = (cur_dir + 1) % MAX_DIRS;
  }
}

// Diagonal Matrix Display Implementation
void diagonal_print(int arr[][MAX_COLS], int rows, int cols) {
  int min_row = 0;          // top    row
  int max_row = (rows - 1); // bottom row
  int min_col = 0;          // left   column
  int max_col = (cols - 1); // right  column
  int row_index, col_index;
  printf("\nDiagonal Print: \n");
  // Fix left side column
  for(col_index=min_col, row_index=min_row; row_index <= (max_row - 1); row_index++){
    int row, col;
    for(row = row_index, col = col_index; (row >= min_row) && (col <= max_col); row--, col++)
      printf("\t%d", arr[row][col]);
    printf("\n");
  }
  // Fix bottom side row
  for(row_index=max_row, col_index=min_col; col_index <= max_col; col_index++){
    int row, col;
    for(row = row_index, col = col_index; (row >= min_row) && (col <= max_col); row--, col++)
      printf("\t%d", arr[row][col]);
    printf("\n");
  }
}

// Horizontal ZigZag Matrix Display Implementation
void zigzag_horizontal(int arr[][MAX_COLS], int rows, int cols) {
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

// Vertical ZigZag Matrix Display Implementation
void zigzag_vertical(int arr[][MAX_COLS], int rows, int cols) {
  int row_index, col_index;
  int max_rows = (rows - 1);
  int max_cols = (cols - 1);
  printf("\nZigzag Print: \n");
  for(col_index = 0; col_index <= max_cols; col_index++) {
    if(col_index % 2 == 0) {
      // Downward print
      for(row_index = 0; row_index <= max_rows; row_index++)
          printf("\t%d", arr[row_index][col_index]);
    }
    else {
      // Upward print
      for(row_index = max_rows; row_index >= 0; row_index--)
          printf("\t%d", arr[row_index][col_index]);
    }
    printf("\n");
  }
}

// Utility to display square matrix
void display_square_matrix(int arr[][TBL_COLS], int rows, int cols) {
  printf("\nSqaure Matrix: \n");
  for(int i=0; i < rows; i++) {
    for(int j=0; j < cols; j++) {
      printf("\t%d", arr[i][j]);
    }
    printf("\n");
  }
}

// Matrix multiplication
void matrix_multiplication(int mat1[][TBL_COLS], int mat2[][TBL_COLS]) {
  int result[TBL_ROWS][TBL_COLS];
  for(int i = 0; i < TBL_ROWS; i++) {
    for (int j = 0; j < TBL_COLS; j++) {
      result[i][j] = 0;
      for(int k = 0; k < TBL_COLS; k++) {
        result[i][j] = result[i][j] + (mat1[i][k] * mat2[k][j]);
      }
    }
  }
  display_square_matrix(result, TBL_ROWS, TBL_COLS);
}

// Helper function to visit neighbours of island
void visit_neighbors(int bin[][BIN_COLS], int row, int col) {
  if((row < BIN_ROWS) && (row >= 0) &&
     (col < BIN_COLS) && (col >= 0) &&
     (bin[row][col] != 0)) {
    // Mark array index as visited
    bin[row][col] = 0;
    // Use static defined neighbours
    static int rowmap[] = {-1,  -1,  -1,   0,   0,   1,   1,   1};
    static int colmap[] = { 0,  -1,   1,  -1,   1,   0,  -1,   1};
    // Recursive call for all 8 neighbours
    for(int n = 0; n < 8; n++) {
      visit_neighbors(bin, (row + rowmap[n]), (col + colmap[n]));
    }
    // Visit 8 neighbours (north, east, south, west, NE, SE, NW, SW)
    // visit_neighbors(bin, row + 1,  col);       Increment row only
    // visit_neighbors(bin, row - 1,  col);       Decrement row only
    // visit_neighbors(bin, row,      col + 1);   Increment col only
    // visit_neighbors(bin, row,      col - 1);   Increment col only
    // visit_neighbors(bin, row + 1,  col + 1);   Increment both
    // visit_neighbors(bin, row - 1,  col - 1);   Decrement both
    // visit_neighbors(bin, row + 1,  col - 1);   Increment row, Decrement col
    // visit_neighbors(bin, row - 1,  col + 1);   Decrement row, Increment col
  }
}

// Function to count number of islands
void count_islands(int bin[BIN_ROWS][BIN_COLS]) {
  int counter = 0;
  for(int row = 0; row < BIN_ROWS; row++) {
    for(int col = 0; col < BIN_COLS; col++) {
      if(bin[row][col] == 1) {
        counter++;
        visit_neighbors(bin, row, col);
      }
    }
  }
  printf("\nCounter: %d", counter);
}

// Utility to flood fill matrix
void flood_fill(int clr[CLR_ROWS][CLR_COLS], int row, int col, int prev, int next) {
  if((row < CLR_ROWS) && (row >= 0) &&
     (col < CLR_COLS) && (col >= 0) &&
     (clr[row][col] == prev)) {
    // Fill with new color
    clr[row][col] = next;
    // Use static defined neighbours
    static int rowfill[] = { 1,  -1,   0,   0};
    static int colfill[] = { 0,   0,   1,  -1};
    // Recursive call for only 4 neighbours
    for(int n = 0; n < 4; n++) {
      flood_fill(clr, (row + rowfill[n]), (col + colfill[n]), prev, next);
    }
    // Visit 4 neighbours (north, south, west, east)
    // flood_fill(bin, row + 1,  col);       Increment row only
    // flood_fill(bin, row - 1,  col);       Decrement row only
    // flood_fill(bin, row,      col + 1);   Increment col only
    // flood_fill(bin, row,      col - 1);   Increment col only
  }
}

void paint_function(int clr[CLR_ROWS][CLR_COLS], int row, int col, int next) {
  if((row < CLR_ROWS) && (row >= 0) &&
     (col < CLR_COLS) && (col >= 0) &&
     (clr[row][col] != next)) {
      int prev = clr[row][col];
      flood_fill(clr, row, col, prev, next);
  }
}

// Display matrix with color codes
void display_paint(int clr[CLR_ROWS][CLR_COLS]) {
  int i, j;
  printf("\nPicture Matrix: \n");
  for(i=0; i < CLR_ROWS; i++) {
    for(j=0; j < CLR_COLS; j++) {
      printf("\t%d", clr[i][j]);
    }
    printf("\n");
  }
}

// Input matrix - 5 x 4
int arr[MAX_ROWS][MAX_COLS] = {
  {2, 4, 6, 8},
  {5, 9, 12, 16},
  {9, 5, 11, 2},
  {2, 11, 5, 9},
  {3, 2, 1, 8},
};

int mat1[TBL_ROWS][TBL_COLS] = {
  {1, 2, 3},
  {2, 1, 2},
  {1, 4, 1},
};

int mat2[TBL_ROWS][TBL_COLS] = {
  {5, 2, 1},
  {4, 1, 1},
  {2, 3, 1},
};

int bin[BIN_ROWS][BIN_COLS] = {
  {1, 1, 0, 0, 0},
  {0, 1, 0, 0, 1},
  {1, 0, 0, 1, 1},
  {0, 0, 0, 0, 0},
  {1, 0, 1, 0, 1}
};

int clr[CLR_ROWS][CLR_COLS] = {
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 0, 0},
  {1, 0, 0, 1, 1, 0, 1, 1},
  {1, 3, 3, 3, 3, 0, 1, 0},
  {1, 1, 1, 3, 3, 0, 1, 0},
  {1, 1, 1, 3, 3, 3, 3, 0},
  {1, 1, 1, 1, 1, 3, 1, 1},
  {1, 1, 1, 1, 1, 3, 3, 1},
};


// Helper function to get determinant of 2D matrix
// Top Row, Bottom Row, Left Column, Right Column
int matrix_2determinant(int** arr, int i, int j, int x, int y) {
  int val = (arr[i][x] * arr[j][y]) - (arr[j][x] * arr[i][y]);
  return val;
}

// Helper function to get determinant of 3D matrix
int matrix_3determinant(int** arr, int row, int col) {
  int value = 0;
  int sign = 1;
  for(int j = 0; j < col; j++) {
    int temp = sign * arr[0][j];
    sign = sign * -1;
    int x = (j + 1) % col;
    int y = (x + 1) % col;
    // Always ensure sorted column order
    if(x > y) {
      int val = x;
      x = y;
      y = val;
    }
    // Specify rows and columns
    value = value + temp * matrix_2determinant(arr, 1, 2, x, y);
  }
  return value;
}

// Main driver function
int main(int argc, char* argv[]) {
  display_paint(clr);
  paint_function(clr, 4, 4, 2);
  display_paint(clr);
  return 0;
}
