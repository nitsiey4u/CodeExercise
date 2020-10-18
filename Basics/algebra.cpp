/***********************************************/
/********   Algebra Maths Solutions   **********/
/***********************************************/
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "limits.h"
#include "math.h"

// Predefined constants
#define MAX_BUFF_SIZE   100000
#define MAX_TEMP_SIZE		256
#define show_bool(val)  ((val) ? "True" : "False")

typedef unsigned long long int  ullint_t;   // 8 bytes unsigned
typedef long long int           llint_t;    // 8 bytes signed
typedef unsigned int            uint_t;     // 4 bytes unsigned

// Find LCM of two numbers - Non Recursive
int lcm_of_numbers(const int numVal1, const int numVal2) {
  if ((numVal1 == 0) || (numVal2 == 0)) {
    printf("\nLCM not defined as one of the numbers is 0.");
    return -1;
  }
  // LCM starts with largest of two numbers as base
  int lcm = (numVal1 > numVal2) ? numVal1 : numVal2;
  // Find LCM exactly divisible by both numbers
  while ((lcm % numVal1 != 0) || (lcm % numVal2 != 0)) {
    // Get next multiple of LCM value
    lcm += lcm;
  }
  return lcm;
}

// Find GCD of two numbers - Non Recursive
int gcd_of_numbers(const int numVal1, const int numVal2) {
  int dividend, divisor;
  if (numVal1 < numVal2) {
    divisor  = numVal1;
    dividend = numVal2;
  } else {
    divisor  = numVal2;
    dividend = numVal1;
  }
  // When divisor becomes 0, dividend hold GCD result
  while(divisor != 0) {
    // Calculate remainder
    int remainder = dividend % divisor;
    // Previous divisor becomes dividend for next iteration
    dividend = divisor;
    // Remainder becomes divisor for next iteration
    divisor = remainder;
  }
  return dividend;
}

// Helper function to display polynomials
void DisplayPolyNomial(const int poly[], const int size) {
  printf("\nPolyNomial: ");
  for(int index = (size - 1); index >= 0; index --) {
    if (poly[index] != 0) {
      const char sign = (poly[index] > 0) ? '+' : '-';
      if((poly[index] > 0) && (index == (size - 1))) {
        printf("%d", poly[index]);
      } else {
        printf("%c%d", sign, abs(poly[index]));
      }
      if (index != 0) {
        printf("x^%d", index);
      }
    }
  }
}

// Add polynomials represented by array
void add_polynomials(const int arr1[], const int m,
                     const int arr2[], const int n) {
  // Result array size will be maximum power of polynomials
  const int size = (m > n) ? m : n;
  int result[size];
  bzero(result, sizeof(result));
  int i, j, k;
  for(i = 0, j = 0, k = 0; i < m && j < n; i++, j++) {
    // Add matching coeffecients with same power for both polynomials
    result[k++] = arr1[i] + arr2[j];
  }
  // Copy coeffecients for remaining powers for polynomial-1
  while(i < m) {
    result[k++] = arr1[i++];
  }
  // Copy coeffecients for remaining powers for polynomial-1
  while(j < n) {
    result[k++] = arr2[j++];
  }
  // Display resultant polynomial
  DisplayPolyNomial(result, size);
}

// Subtract polynomials represented by array
void subtract_polynomials(const int arr1[], const int m,
                          const int arr2[], const int n) {
  // Result array size will be maximum power of polynomials
  const int size = (m > n) ? m : n;
  int result[size];
  bzero(result, sizeof(result));
  int i, j, k;
  for(i = 0, j = 0, k = 0; i < m && j < n; i++, j++) {
    // Subtract matching coeffecients with same power for both polynomials
    result[k++] = arr1[i] - arr2[j];
  }
  // Copy coeffecients for remaining powers for polynomial-1
  while(i < m) {
    result[k++] = arr1[i++];
  }
  // Copy coeffecients for remaining powers for polynomial-2
  while(j < n) {
    result[k++] = arr2[j++];
  }
  // Display resultant polynomial
  DisplayPolyNomial(result, size);
}


// Multiply polynomials represented by array
void multiply_polynomials(const int arr1[], const int m,
                          const int arr2[], const int n) {
  // Result array size will be sum of power for polynomials
  // -1 is to be remove common constant values from polynomials
  const int size = (m + n - 1);
  int result[size];
  bzero(result, sizeof(result));
  // Outer lopp over polynomial-1
  for(int i = 0; i < m; i++) {
    // Inner loop over polynomial-2
    for(int j = 0; j < n; j++) {
      // Product of powers => Addition to find new power
      const int pos = i + j;
      // For new power, multiply the coeffecients
      result[pos] += arr1[i] * arr2[j];
    }
  }
  // Display resultant polynomial
  DisplayPolyNomial(result, size);
}

// Find solution for linear equation with single variable X
// ax+bx+c = d (where a,b = coeffecients ; c,d = constants)
void solve_linear_equation(const char* equation) {
  int signVal = 1;      // Default postive value
  bool toggle = false;  // LHS = false, RHS = true
  int index, intVal, intSum, varSum;
  for(index = 0, intVal = 0, intSum = 0, varSum = 0; index < strlen(equation); index++) {
    if((equation[index] >= '0') && (equation[index] <= '9')) {
      // Extract integer number (intval)
      intVal = (intVal * 10) + (equation[index] - '0');
      // For first digit specify exact sign
      if(abs(intVal)/10 == 0) {
        intVal = (signVal * intVal);
      }
    } else if(equation[index] == 'x') {
      // Consume intval into coeffecient total (varSum)
      if(intVal != 0) {
        varSum = varSum + intVal;
      } else {
        varSum = varSum + signVal;
      }
      // Reset intval = 0
      intVal = 0;
    } else if((equation[index] == '+')||(equation[index] == '-')) {
      // Consume intval into constant total (intSum)
      if (intVal != 0) {
        intSum = intSum + intVal;
      }
      // Reset intval = 0
      intVal = 0;
      // Decide sign value based on LHS or RHS
      if(toggle) {
        // For RHS, opposite sign values
        signVal = (equation[index] == '-') ? 1 : -1;
      } else {
        // For LHS, default sign values
        signVal = (equation[index] == '+') ? 1 : -1;
      }
    } else if(equation[index] == '=') {
      // Consume intval into constant total (intSum)
      if(intVal != 0) {
        intSum = intSum + intVal;
      }
      // Reset intval = 0
      intVal = 0;
      // Toggle sign for RHS variables and values
      signVal = -1;
      toggle  = true;
    }
  }
  // Equation end, consume intval into constant total (intSum)
  if(intVal != 0) {
    intSum = intSum + intVal;
  }
  printf("\nEquation: %s", equation);
  // Ideally, coeffecient total (varSum) should never be 0
  if(varSum == 0) {
    // Check if constant total (intSum) is 0
    if (intSum == 0) {
      // X = X
      printf("\nInfinite solutions");
    } else {
      // X = X + 2
      printf("\nNo solution");
    }
  } else {
    // x + 5 - 3 + x = 6 + x - 2 (Solution: x = 2)
    // All totals are moved to LHS, for RHS solution multiply by -1
    // - constant total (intSum) / coeffecient total (varSum)
    printf("\nSolution: x = %d", ((intSum * -1) / (varSum)));
  }
}

// Helper function to get determinant of 2D matrix
// Top Row, Bottom Row, Left Column, Right Column
int get2Determinant(int** arr, int i, int j, int x, int y) {
  int val = (arr[i][x] * arr[j][y]) - (arr[j][x] * arr[i][y]);
  return val;
}

// Helper function to get determinant of 3D matrix
int get3Determinant(int** arr, int row, int col) {
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
    value = value + temp * get2Determinant(arr, 1, 2, x, y);
  }
  return value;
}

// Helper function to parse equation
void parseEquation(const char* equation, int* array, int* result) {
  int sign = 1;
  int intVal = 0;
  int varCnt = 0;
  for(int index = 0; index < strlen(equation); index++) {
    if(('0' <= equation[index])&&(equation[index] <= '9')) {
      int digit = equation[index] - '0';
      //printf("\nDigit: %d, Sign: %d", digit, sign);
      intVal = intVal * 10 + digit;
      if((intVal/10) == 0) {
        intVal = intVal * sign;
      }
    } else if ((equation[index] == '-')||(equation[index] == '+')) {
      //printf("\nSign: %d, Char: %c", sign, equation[index]);
      sign = (equation[index] == '-')? -1 : 1;
    } else if (equation[index] == '=') {
      array[varCnt++] = (intVal == 0)? sign : intVal;
      intVal = 0;
      sign = 1;
    } else {
      //printf("\nSign: %d, Char: %c", sign, equation[index]);
      array[varCnt++] = (intVal == 0)? sign : intVal;
      intVal = 0;
    }
  }
  *result = intVal;
}

// Helper function to swap values with result
void swapResultant(int** values, int** result, int count, int col) {
  for(int row = 0; row < count; row++) {
    int temp = values[row][col];
    values[row][col] = result[row][0];
    result[row][0] = temp;
  }
}

void showResultant(int** values, int** result, int count) {
  printf("\nMatrix: ");
  for(int rowIndex = 0; rowIndex < count; rowIndex++) {
    printf("\n");
    for(int colIndex = 0; colIndex < count; colIndex++) {
      printf("\t%d", values[rowIndex][colIndex]);
    }
    printf("\t%d", result[rowIndex][0]);
  }
}

// Find solution for linear equation with multiple variables X
// ax+by+cz = d (where a,b,c = coeffecients ; d = constants)
void solve_multiple_equations(const char* equations[], const int count) {
  int** arrValues = (int**) malloc(sizeof(int*) * count);
  int** arrResult = (int**) malloc(sizeof(int*) * count);
  for(int index = 0; index < count; index++) {
    arrValues[index] = (int*) malloc(sizeof(int) * count);
    arrResult[index] = (int*) malloc(sizeof(int) * 1);
    parseEquation(equations[index], arrValues[index], arrResult[index]);
  }
  // Get determinant D
  int* determinant = (int*) malloc(sizeof(int) * (count + 1));
  showResultant(arrValues, arrResult, count);
  determinant[0] = get3Determinant(arrValues, count, count);
  printf("\nDeterminant: %d", determinant[0]);
  // Get determinant D1, D2, D3
  for(int index = 0; index < count; index++) {
    swapResultant(arrValues, arrResult, count, index);
    showResultant(arrValues, arrResult, count);
    determinant[index+1] = get3Determinant(arrValues, count, count);
    printf("\nDeterminant: %d", determinant[index+1]);
    swapResultant(arrValues, arrResult, count, index);
  }
  // Print solutions
  if (determinant[0] == 0) {
    bool flag = true;
    for(int index = 1; (flag)&&(index <= count); index++) {
      flag = (determinant[0] == determinant[index]);
    }
    if(flag) {
      // Infinite solution
      printf("\nInfinite solutions.");
    } else {
      // Invalid solution
      printf("\nInvalid solution.");
    }
  } else {
    // Valid solutions
    for(int index = 1; index <= count; index++) {
      printf("\nVar-%d = %d", index, (determinant[index]/determinant[0]));
    }
  }
  // Cleanup
  for(int index = 0; index < count; index++) {
    free(arrValues[index]);
    free(arrResult[index]);
  }
  free(arrValues);
  free(arrResult);
  free(determinant);
}

// N(N+1)/2
int sum_of_numbers(const int arrNumbers[], const size_t arrSize) {
  return (arrSize * (arrSize + 1))/2;
}

// N(N+1)(2N+1)/6
int sum_of_squares(const int arrNumbers[], const size_t arrSize) {
  return (arrSize * (arrSize + 1) * ((2 * arrSize) + 1))/6;
}

// square of N(N+1)/2
int sum_of_cubes(const int arrNumbers[], const size_t arrSize) {
  const int squareVal = arrSize * arrSize;
  return (squareVal * (squareVal + (2 * arrSize) + 1)) / 4;
}

// Get Nth term in arithmetic series T(N)
uint_t get_nth_term(const uint_t numFirst, const uint_t numTerm, const uint_t numConstant) {
  return numFirst + (numTerm - 1) * numConstant;
}

// Get Nth odd term in arithmetic series
uint_t get_nth_odd(const uint_t numTerm) {
  return get_nth_term(1, numTerm, 2);
}

// Get Nth even term in arithmetic series
uint_t get_nth_even(const uint_t numTerm) {
  return get_nth_term(0, numTerm, 2);
}

// Get arithmetic sum of numbers S(N)
int get_arithmetic_mean(const int arrNumbers[], const size_t arrSize) {
  const int firstTerm = arrNumbers[0];
  const int constDiff = arrNumbers[1] - arrNumbers[0];
  const int numValues = arrSize;
  return (numValues/2) * ((2 * firstTerm) + ((numValues - 1) * constDiff));
}

// Helper function to get factorial of given number
ullint_t getFactorial(const ullint_t numValue) {
  if (numValue > 1) {
    return numValue * getFactorial(numValue - 1);
  }
  return 1;
}

// Permutations (NPR) = N!/(N-R)!
ullint_t permutation_npr_value(const uint_t numSize, const uint_t repCount) {
  return getFactorial(numSize) / getFactorial(numSize - repCount);
}

// Combinations (NPR) = N!/R!(N-R)!
ullint_t combination_ncr_value(const uint_t numSize, const uint_t repCount) {
  return getFactorial(numSize) / (getFactorial(repCount) * getFactorial(numSize - repCount));
}

int main() {
  const char* equations[] = {
    "2x-y+3z=9",
    "x+y+z=6",
    "x-y+z=2"
  };

  solve_multiple_equations(equations, 3);

}
