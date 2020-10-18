/***********************************************/
/********   Matrix Related Problems   **********/
/***********************************************/
#include <cstdio>
#include <cstdlib>
#include <algorithm>

#define MAX(a,b) ((a > b)?(a):(b))

// Matrix for range queries
#define RNG_ROWS 3
#define RNG_COLS 4

// Matrix for diagonal, spiral printing
#define MAX_ROWS 5    // Matrix 5 x 4
#define MAX_COLS 4    // Matrix 5 x 4

// Square matrix for add/subtract/multiply operations
#define TBL_ROWS 3    // Square Matrix 3 x 3
#define TBL_COLS 3    // Square Matrix 3 x 3

// Binary matrix for island counting - 8 neighbours
#define BIN_ROWS 5    // Matrix 5 x 5
#define BIN_COLS 5

// Color coded matrix for flood fill - 4 neighbours
#define CLR_ROWS 8
#define CLR_COLS 8

//  Maximum directions for matrix traversal
#define MAX_DIRS 4
#define MAX_NGBR 8

// Connected components matrix for grid grouping - 4 neighbours
#define GRID_ROWS 6    // Matrix 6 x 8
#define GRID_COLS 8

// Position in matrix (row, col)
struct Position {
  int row;
  int col;
};
typedef struct Position POS;

// Class to hold all integers values and their cumulative sum in matrix
class RectangleSum {
private:
  int   max_rows;   // Max rows
  int   max_cols;   // Max columns

  int** arr_vals;   // Matrix of integers (input)
  int** cum_sums;   // Matrix of cumulative sum of integers
public:
  // Constructor to initialize matrix and cumulative sum
  RectangleSum(int arr[][RNG_COLS], int rows, int cols) {
    max_rows = rows;
    max_cols = cols;
    // Dynamically allocate both arrays
    arr_vals = (int**) calloc(max_rows, sizeof(int*));
    cum_sums = (int**) calloc(max_rows, sizeof(int*));
    for(int index = 0; index < max_rows; index++) {
      arr_vals[index] = (int*) calloc(max_cols, sizeof(int));
      cum_sums[index] = (int*) calloc(max_cols, sizeof(int));
    }
    int row, col, sum;
    // Populate row 0
    for(row = 0, col = 0, sum = 0; col < max_cols; col++) {
      arr_vals[row][col] = arr[row][col];
      sum = sum + arr_vals[row][col];
      cum_sums[row][col] = sum;
    }
    // Populate column 0
    for(row = 0, col = 0, sum = 0; row < max_rows; row++) {
      arr_vals[row][col] = arr[row][col];
      sum = sum + arr_vals[row][col];
      cum_sums[row][col] = sum;
    }
    // Populate remaining rows and columns
    for(int row = 1; row < max_rows; row++) {
      for(int col = 1; col < max_cols; col++) {
        arr_vals[row][col] = arr[row][col];
        int curr_sum = cum_sums[row][col - 1] +     // Left Column
                       cum_sums[row - 1][col] +     // Top Row
                       arr[row][col];               // Current Value
        int prev_sum = cum_sums[row - 1][col - 1];  // Diagonal Value
        cum_sums[row][col] = curr_sum - prev_sum;   // Rectangular sum
      }
    }
  }
  // Destructor
  ~RectangleSum() {
    for(int index = 0; index < max_rows; index++) {
      free(arr_vals[index]);
      free(cum_sums[index]);
    }
    free(arr_vals);
    free(cum_sums);
  }
  // The cumulative sum for matrix rectangle starts from (0,0)
  // For left-top and right-bottom positions find sum of integers in rectangle
  int get_ranged_sum(Position& start, Position& end) {
    if(start.row == 0) {
      if(start.col == 0) {
        // All cumulative sums are indexed at (0, 0) by default
        return cum_sums[end.row][end.col];
      } else {
        // Remove unused left-most column
        return cum_sums[end.row][end.col] -
               cum_sums[end.row][start.col - 1];
      }
    } else {
      if(start.col == 0) {
        // Remove unused top-most row
        return cum_sums[end.row][end.col] -
               cum_sums[start.row - 1][end.col];
      } else {
        // Remove unused left-most column and top-most row
        int remval = cum_sums[end.row][start.col - 1] +
                     cum_sums[start.row - 1][end.col];
        // Diagonally previous element of start needs to be added back
        // again because above remove has overlappingly removed element
        int diaval = cum_sums[start.row - 1][start.col - 1];
        // From cumulative sum of destination remove unused portions
        // and add diagonally previous element of source (as it was removed twice)
        return (cum_sums[end.row][end.col] - remval) + diaval;
      }
    }
    return -1;
  }
  // Display input integers
  void display_arr_value() {
    printf("\nArray Values: ");
    for(int row = 0; row < max_rows; row++) {
      printf("\n");
      for(int col = 0; col < max_cols; col++) {
        printf("\t%d", arr_vals[row][col]);
      }
    }
  }
  // Display cumulative sum
  void display_sum_total() {
    printf("\nCumulative Sum: ");
    for(int row = 0; row < max_rows; row++) {
      printf("\n");
      for(int col = 0; col < max_cols; col++) {
        printf("\t%d", cum_sums[row][col]);
      }
    }
  }
};

// Driver for Rectangle Sum
void execute_rectangle_sum() {
  // Default array
  int arr[RNG_ROWS][RNG_COLS] = {
    {1, 3,  5,  7},
    {2, 4,  6,  8},
    {9, 10, 11, 12},
  };
  RectangleSum range(arr, RNG_ROWS, RNG_COLS);
  range.display_arr_value();
  range.display_sum_total();
  Position start, end;
  int row1, col1, row2, col2;
  for(row1 = 0, col1 = 0; col1 < (RNG_COLS - 1) && row1 < (RNG_ROWS - 1); col1++, row1++) {
    for(row2 = (row1 + 1), col2 = (col1 + 1); col2 < RNG_COLS; col2++) {
      start.row = row1;
      start.col = col1;
      end.row   = row2;
      end.col   = col2;
      printf("\nTotal Sum: %d %d -> %d %d \t = %d",
        start.row, start.col, end.row, end.col,
        range.get_ranged_sum(start, end));
    }
  }
}

// Utility to dynamically allocated 2-D matrix
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
  {1, 1, 1, 1, 1},
  {0, 0, 0, 1, 0},
  {1, 0, 1, 1, 1}
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

// Helper function to create, initialize and display 3D matrix
// 3D matrix = array of 2D matrices
void allocate_3darray(int blocks, int rows, int cols) {
  int*** array = (int***)malloc(sizeof(int**) * blocks);
  int counter  = 1;
  // Allocate (dynamic) and initialize 3D matrix
  for(int block = 0; block < blocks; block++) {
    array[block] = (int**)malloc(sizeof(int*) * rows);
    for(int row = 0; row < rows; row++) {
      array[block][row] = (int*)malloc(sizeof(int) * cols);
      for(int col = 0; col < cols; col++) {
        array[block][row][col] = counter++;
      }
    }
  }
  // Display 3D matrix
  for(int block = 0; block < blocks; block++) {
    printf("\n[%d]: ", block);
    for(int row = 0; row < rows; row++) {
      printf("\n");
      for(int col = 0; col < cols; col++) {
        printf("\t%d", array[block][row][col]);
      }
    }
    printf("\n");
  }
  // Deallocate
  for(int block = 0; block < blocks; block++) {
    for(int row = 0; row < rows; row++) {
      free(array[block][row]);
    }
    free(array[block]);
  }
  free(array);
}

// Visit array elements
int visit_elements(int bin[BIN_ROWS][BIN_COLS], int row, int col) {
    static int row_vals[MAX_NGBR] = { 0,  0, +1, +1, +1, -1, -1, -1};
    static int col_vals[MAX_NGBR] = {+1, -1, -1,  0, +1, -1,  0, +1};
    int counter = 0;
    if(((row >= 0) && (row < BIN_ROWS)) &&
       ((col >= 0) && (col < BIN_COLS)) &&
       (bin[row][col] == 1)) {
      counter = 1;
      bin[row][col] = 0;
      for(int index = 0; index < MAX_NGBR; index++) {
        int row_index = row + row_vals[index];
        int col_index = col + col_vals[index];
        counter += visit_elements(bin, row_index, col_index);
      }
    }
    return counter;
}


// Get largest region size of connected 1's - O(MN)
void largest_region_size(int bin[BIN_ROWS][BIN_COLS]) {
  int region = 0;
  for(int row = 0; row < BIN_ROWS; row++) {
    for(int col = 0; col < BIN_COLS; col++) {
      if(bin[row][col] == 1) {
        int retval = visit_elements(bin, row, col);
        region = (retval > region) ? retval : region;
      }
    }
  }
  printf("\nMax Region: %d", region);
}

// Find longest connected 1's - O(N2)
// Consider only forward direction (Right and Down)
void longest_connected_ones(int bin[BIN_ROWS][BIN_COLS]) {
  int region = 0;
  int max_row = 0;
  int max_col = 0;
  for(int row = 0; row < BIN_ROWS; row++) {
    for(int col = 0; col < BIN_COLS; col++) {
      // Check if element is part of grid-1
      if(bin[row][col] == 1) {
        // Get value of above (TOP) element
        int row_val = (row == 0) ? 0 : bin[row - 1][col];
        // Get value of previous (LEFT) element
        int col_val = (col == 0) ? 0 : bin[row][col - 1];
        // Use previous max and add current 1
        bin[row][col] = MAX(row_val, col_val) + 1;
        // Update max region and indices
        if(bin[row][col] > region) {
          region = bin[row][col];
          max_row = row;
          max_col = col;
        }
      } else {
        // Set value as 0
        bin[row][col] = 0;
      }
    } // Inner loop
  } // Outer loop

  // Backtrack to initialize result array
  const int length = region;
  int pre_row = max_row;
  int pre_col = max_col;
  int result[BIN_ROWS][BIN_COLS] = {0};
  for(int row = max_row; (region > 0) && (row >= 0); row--) {
    for(int col = max_col; (region > 0) && (col >= 0); col--) {
      if((bin[row][col] == region) &&
         (row <= pre_row) && (col <= pre_col)) {
        result[row][col] = 1;
        pre_row = row;
        pre_col = col;
        region --;
      }
    }
  }

  // Display longest path
  printf("\nLongest connected path (%d) of 1's: ", length);
  for(int row = 0; row < BIN_ROWS; row++) {
    printf("\n");
    for(int col = 0; col < BIN_COLS; col++) {
      printf("\t%d", result[row][col]);
    }
  }
}

// Grid matrix of connected components
int grid[GRID_ROWS][GRID_COLS] = {
  { 1, 4, 4, 4, 4, 3, 3, 1 },
  { 2, 1, 1, 4, 3, 3, 1, 1 },
  { 3, 2, 1, 1, 2, 3, 2, 1 },
  { 3, 3, 2, 1, 2, 2, 2, 2 },
  { 3, 1, 3, 1, 1, 4, 4, 4 },
  { 1, 1, 3, 1, 1, 4, 4, 4 } };

// Display Grid
void display_grid(int arr[][GRID_COLS]) {
  printf("\nGrid: ");
  for(int row = 0; row < GRID_ROWS; row++) {
    printf("\n");
    for(int col = 0; col < GRID_COLS; col++) {
      printf("\t%d", arr[row][col]);
    }
  }
}

// Recursively visit grid neighbours matching key (same group)
int grid_neighbours(int arr[][GRID_COLS], int visit[][GRID_COLS],
                    const int row, const int col,
                    const int key, const int group) {
    int counter = 0;
    static int row_map[MAX_DIRS] = {-1, +1,  0,  0};
    static int col_map[MAX_DIRS] = { 0,  0, -1, +1};
    if((0 <= row) && (row < GRID_ROWS) &&
       (0 <= col) && (col < GRID_COLS) &&
       (visit[row][col] == 0) &&
       (arr[row][col] == key)) {
        counter = 1;
        visit[row][col] = group;
        for(int index = 0; index < MAX_DIRS; index++) {
          counter += grid_neighbours(arr, visit,
                                     (row + row_map[index]), (col + col_map[index]),
                                     key, group);
      } // For loop
    } // If block
    return counter;
}

// Find largest connected components - O(MN)
void largest_connected_component(int arr[GRID_ROWS][GRID_COLS]) {
  int visit[GRID_ROWS][GRID_COLS] = {0};
  int group_num = 0;
  int max_group = 0;
  int max_value = 0;
  for(int row = 0; row < GRID_ROWS; row++) {
    for(int col = 0; col < GRID_COLS; col++) {
      if(visit[row][col] == 0) {
        // Assign new group number for un-visited key element
        group_num++;
        const int key = arr[row][col];
        // Find grid neighbours for specific key element
        int val = grid_neighbours(arr, visit, row, col, key, group_num);
        // Save maximum group information
        if(val > max_value) {
          max_value = val;
          max_group = group_num;
        }
      }
    } // Inner Loop
  } // Outer Loop
  printf("\nMax Group Size: %d", max_value);
  printf("\nMax Group Number: %d", max_group);

  // Show grid with results
  for(int row = 0; row < GRID_ROWS; row++) {
    printf("\n");
    for(int col = 0; col < GRID_COLS; col++) {
      if(visit[row][col] == max_group) {
        printf("\t%d", arr[row][col]);
      } else {
        printf("\t.");
      }
    }
  }
}

// Main driver function
int main(int argc, char* argv[]) {
  // display_paint(clr);
  // paint_function(clr, 4, 4, 2);
  // display_paint(clr);
  // execute_rectangle_sum();

  //longest_connected_ones(bin);
  display_grid(grid);
  largest_connected_component(grid);
  // display_grid(grid);
  return 0;
}
