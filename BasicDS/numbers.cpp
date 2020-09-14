#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "limits.h"
#include "math.h"

#define MAX_BUFF_SIZE 100000
#define show_bool(val) ((val) ? "True" : "False")

typedef unsigned long long int  ullint_t;
typedef long long int           llint_t;
typedef unsigned int            uint_t;

// Converts ASCII String to Integer (MSB)
llint_t StringtoNumericMSB(const char* strValue) {
  llint_t       intValue = 0;
  const int     signFlag = (strValue[0] == '-') ? -1 : 1;
  const uint_t  limitPos = (signFlag == 1) ? 0 : 1;
  for (uint_t indexPos = limitPos; indexPos < strlen(strValue); indexPos++) {
    uint_t posval = strValue[indexPos] - '0';
    intValue = (intValue * 10) + posval;
  }
  return intValue * signFlag;
}

// Converts ASCII String to Integer (LSB)
llint_t StringtoNumericLSB(const char* strValue) {
  llint_t      intValue = 0;
  const int    signFlag = (strValue[0] == '-') ? -1 : 1;
  const int    limitPos = (signFlag == 1) ? 0 : 1;
  int          indexPos = strlen(strValue) - 1;
  for (uint_t factorPos = 1; indexPos >= limitPos; indexPos--, (factorPos = factorPos * 10)) {
      uint_t posval = strValue[indexPos] - '0';
      intValue = intValue + (posval * factorPos);
  }
  return intValue * signFlag;
}

uint_t CountNumberOfDigits(const int numValue) {
  uint_t counter = 1;
  for(int value = numValue; value > 10; (value = value / 10)) {
    counter++;
  }
  return counter;
}

uint_t ExtractDigit(const ullint_t numValue, const uint_t digitPos) {
  ullint_t factorVal = pow(10, (digitPos - 1));
  ullint_t resultVal = numValue / factorVal;
  return resultVal % 10;
}
// Check if number is perfect square
bool isPerfectSquare(const uint_t numVal) {
  uint_t index;
  for(index = 1; (index * index) < numVal; index++);
  return ((index * index) == numVal);
}

ullint_t NumberFactorial(const ullint_t numValue) {
  if (numValue > 1) {
    return numValue * NumberFactorial(numValue - 1);
  }
  return 1;
}

bool IsValidPower(const ullint_t numValue, const ullint_t powFactor) {
  ullint_t tmpValue;
  for(tmpValue = numValue; tmpValue > powFactor; tmpValue = (tmpValue / powFactor));
  return (tmpValue == powFactor);
}

void DisplayNumbertoString(const int numValue) {
  char* strValue = NULL;
  const uint_t numDigits = log10(abs(numValue)) + 1;
  int beginIndex, endIndex;
  if(numValue > 0) {
    strValue = (char*) malloc (sizeof(char) * (numDigits + 1));
    beginIndex = 0;
    endIndex = numDigits;
    strValue[endIndex] = '\0';
    endIndex --;
  } else {
    strValue = (char*) malloc (sizeof(char) * (numDigits + 2));
    beginIndex = 0;
    strValue[beginIndex] = '-';
    beginIndex++;
    endIndex = numDigits + 1;
    strValue[endIndex] = '\0';
    endIndex --;
  }
  for (int divident = abs(numValue); divident >= 1; (divident = divident / 10)) {
    int remainder = divident % 10;
    strValue[endIndex] = '0' + remainder;
    printf("\nString Position %d = %d", endIndex, remainder);
    endIndex --;
  }
  printf("\nString Value = %s", strValue);
  free(strValue);
}

void DisplayFiboNacciSequenceNonRec(const uint_t numCount) {
  uint_t sequence[numCount];
  for(uint_t indexPos = 1; indexPos <= numCount; indexPos++) {
    if (indexPos < 3) {
      sequence[indexPos] = (indexPos == 1) ? 0 : 1;
      printf(" %d ", sequence[indexPos]);
    } else {
      sequence[indexPos] = sequence[indexPos - 1] +
                           sequence[indexPos - 2];
      printf(" %d ", sequence[indexPos]);
    }
  }
}

void FiboNacciRecSeries(const uint_t numCount, const uint_t indexPos, uint_t* sequence) {
  if(indexPos < numCount) {
    if (indexPos < 2) {
      sequence[indexPos] = (indexPos == 0) ? 0 : 1;
    }
    else {
      sequence[indexPos] = sequence[indexPos - 1] +
                           sequence[indexPos - 2];
    }
    FiboNacciRecSeries(numCount, (indexPos + 1), sequence);
  }
}

void DisplayFiboNacciSequenceRec(const uint_t numCount) {
  uint_t* sequence = (uint_t*) malloc(sizeof(uint_t) * numCount);
  FiboNacciRecSeries(numCount, 0, sequence);
  for (uint_t indexPos = 0; indexPos < numCount; indexPos++) {
    printf(" %d ", sequence[indexPos]);
  }
  free(sequence);
}

uint_t GetFiboNacciNumber(const uint_t numCount) {
  if (numCount > 1) {
    return GetFiboNacciNumber(numCount - 1) +
           GetFiboNacciNumber(numCount - 2);
  }
  return (numCount == 0) ? 0 : 1;
}

uint_t GetNextFiboNacciNumber(const uint_t numCount) {
  uint_t nextValue = round(numCount * ((sqrt(5) + 1) / 2));
  return nextValue;
}

bool IsValidFiboNacci(const uint_t numValue) {
  uint_t baseSquare = 5 * pow(numValue, 2);
  return isPerfectSquare(baseSquare + 4) || isPerfectSquare(baseSquare - 4);
}

bool IsValidPrime(const uint_t numValue) {
  bool testFlag;
  if (numValue == 2) {
    testFlag = true;
  } else if((numValue <= 1) || ((numValue % 2) == 0)) {
    testFlag = false;
  } else {
    for(uint_t counter = 2; counter * counter <= numValue; counter++) {
      printf("\nTesting factor: %d", counter);
      if ((numValue % counter) == 0) {
        printf("\nFound factor: %d", counter);
        testFlag = false;
        break;
      }
    }
  }
  return testFlag;
}

int FindHCF(const int numVal1, const int numVal2) {
  int minValue, maxValue;
  if (numVal1 < numVal2) {
    minValue = numVal1;
    maxValue = numVal2;
  } else {
    minValue = numVal2;
    maxValue = numVal1;
  }
  if (minValue == 0) {
    return maxValue;
  }
  return FindHCF((maxValue % minValue), minValue);
}

int FindGCD(const int numVal1, const int numVal2) {
  int dividend, divisor, gcd;
  if (numVal1 < numVal2) {
    divisor  = numVal1;
    dividend = numVal2;
  } else {
    divisor  = numVal2;
    dividend = numVal1;
  }
  for (gcd = dividend; divisor != 0; dividend = gcd) {
    gcd = divisor;
    divisor = dividend % divisor;
  }
  return gcd;
}

// Find LCM - Non Recursive
int FindNonRecLCM(const int numVal1, const int numVal2) {
  if ((numVal1 == 0) || (numVal2 == 0)) {
    printf("\nLCM not defined as one of the numbers is 0");
    return INT_MAX;
  }
  // LCM starts with largest of two numbers as base
  int lcmValue = (numVal1 > numVal2) ? numVal1 : numVal2;
  // Find LCM exactly divisible by both numbers
  while ((lcmValue % numVal1 != 0) || (lcmValue % numVal2 != 0)) {
    // Increment LCM value if exact least multiple not found
    ++lcmValue;
  }
  return lcmValue;
}

int FindRecLCM(const int numVal1, const int numVal2, const int lcmValue) {
  if ((lcmValue % numVal1 == 0) && (lcmValue % numVal2 == 0)) {
    return lcmValue;
  }
  return FindRecLCM(numVal1, numVal2, (lcmValue + 1));
}

void DisplayPrimeNumbers(const uint_t numValue) {
  printf("\nPrime Numbers below %d: ", numValue);
  uint_t counter, lower, upper;
  for(counter = 1, lower = 2, upper = 3;  lower <= numValue; counter++) {
    // Check lower
    if (lower <= numValue) {
      printf("\t%d", lower);
    }
    // Check upper
    if (upper <= numValue) {
      printf("\t%d", upper);
    }
    const uint_t tmpValue = 6 * counter;
    lower = tmpValue - 1;
    upper = tmpValue + 1;
  }
}

void ShowArrayGCDLCM(const int arrNumbers[], const size_t arrSize) {
  int arrLCM[arrSize];
  int arrGCD[arrSize];
  int index, counter;
  for(index = 0; index < arrSize; index++) {
    if (index == 0) {
      arrLCM[index] = arrNumbers[index];
      arrGCD[index] = arrNumbers[index];
    } else {
      arrLCM[index] = FindNonRecLCM(arrLCM[index - 1], arrNumbers[index]);
      arrGCD[index] = (arrNumbers[index - 1] * arrNumbers[index]) / arrLCM[index];
    }
  }
  printf("\nLCM: %d", arrLCM[index-1]);
  printf("\nGCD: %d", arrGCD[index-1]);
}

int GetArrayLCM(const int arrNumbers[], const size_t arrSize) {
  int arrLCM[arrSize];
  int index, counter;
  for(index = 0; index < arrSize; index++) {
    if (index == 0) {
      arrLCM[index] = arrNumbers[index];
    } else {
      arrLCM[index] = FindNonRecLCM(arrLCM[index - 1], arrNumbers[index]);
    }
  }
  return arrLCM[index-1];
}

int GetArrayGCD(const int arrNumbers[], const size_t arrSize) {
  int arrGCD[arrSize];
  int index, counter;
  for(index = 0; index < arrSize; index++) {
    if (index == 0) {
      arrGCD[index] = arrNumbers[index];
    } else {
      arrGCD[index] = FindGCD(arrGCD[index - 1], arrNumbers[index]);
    }
  }
  return arrGCD[index-1];
}

uint_t GetNthTerm(const uint_t numFirst, const uint_t numTerm, const uint_t numConstant) {
  return numFirst + (numTerm - 1) * numConstant;
}

uint_t GetNthOddNumber(const uint_t numTerm) {
  return GetNthTerm(1, numTerm, 2);
}

uint_t GetNthEvenNumber(const uint_t numTerm) {
  return GetNthTerm(2, numTerm, 2);
}

int GetArithmeticMean(const int arrNumbers[], const size_t arrSize) {
  const int firstTerm = arrNumbers[0];
  const int constDiff = arrNumbers[1] - arrNumbers[0];
  const int numValues = arrSize;
  return (numValues/2) * ((2 * firstTerm) + ((numValues - 1) * constDiff));
}

int GetSumOfNumbers(const int arrNumbers[], const size_t arrSize) {
  // N(N+1)/2
  return (arrSize * (arrSize + 1))/2;
}

int GetSumOfSquares(const int arrNumbers[], const size_t arrSize) {
  //N(N+1)(2N+1)/6
  return (arrSize * (arrSize + 1) * ((2 * arrSize) + 1))/6;
}

int GetSumOfCubes(const int arrNumbers[], const size_t arrSize) {
  const int squareVal = arrSize * arrSize;
  return (squareVal * (squareVal + (2 * arrSize) + 1)) / 4;
}

int MultiplyResult(int* result, const int size, const int base) {
  int carry, index;
  for (index = 0, carry = 0; index < size; index++) {
    const uint_t output = result[index] * base + carry;
    result[index] = output % 10;
    carry = output / 10;
  }
  // Till there is no carry
  while (carry != 0) {
    result[index] = carry % 10;
    carry = carry / 10;
    index ++;
  }
  return index;
}

void PowerOfLargeNumber(const int base, const int power) {
  int arrResult[MAX_BUFF_SIZE];
  int resultSize = 0;
  if (base == 0) {
    arrResult[resultSize++] = 0;
  } else if (power == 0) {
    arrResult[resultSize++] = 1;
  } else {
    int absval = abs(base);
    // Initialize result array
    for(int value = absval; value != 0; value = value / 10) {
      arrResult[resultSize] = value % 10;
      resultSize ++;
    }
    // Multiply number by itself
    for(int index = 1; index < power; index ++) {
      resultSize = MultiplyResult(arrResult, resultSize, absval);
    }
  }
  // Display final result
  const char signChar = ((base < 0) && (power % 2 != 0)) ? '-' : '+';
  printf("\n%d^%d gives %d-digit result: %c",
    base, power, resultSize, signChar);
  for (int index = (resultSize - 1); index >= 0; index--) {
    printf("%d", arrResult[index]);
  }
}

ullint_t GetValueofNPR(const uint_t numSize, const uint_t repCount) {
  return NumberFactorial(numSize) / NumberFactorial(numSize - repCount);
}

ullint_t GetValueofNCR(const uint_t numSize, const uint_t repCount) {
  return NumberFactorial(numSize) / (NumberFactorial(repCount) * NumberFactorial(numSize - repCount));
}

void TestArray(int arr[], int & size) {
  for(int index = 0; index < size; index++) {
    arr[index]--;
  }
}

void FindRoots(const int a, const int b, const int c) {
  double baseVal = (b * b) - (4 * a * c);
  double sqrtVal = sqrt(abs(baseVal));

  if(baseVal > 0) {
    printf("\nRoots are real and different: ");
    printf("\n%.3f\n%.3f", ((-b + sqrtVal)/(2 * a)), ((-b - sqrtVal)/(2 * a)));
  } else if (baseVal == 0) {
    printf("\nRoots are real and same: ");
    double tempVal = (-b / (2 * a));
    printf("\n%.2f\n%.2f", tempVal, tempVal);
  } else {
    printf("\nRoots are complex: ");
    double tempVal = double(-b)/(2 * a);
    printf("\n%.2f+i%.2f\n%.2f-i%.2f", tempVal, sqrtVal, tempVal, sqrtVal);
  }
}

double FindNthRoot(const double numberVal, const double rootVal) {
  const double precision = 0.000001;
  double resultVal;
  for (resultVal = 1; pow(resultVal, rootVal) <= numberVal; resultVal++);
  for (--resultVal; pow(resultVal, rootVal) < numberVal; resultVal += precision);
  return resultVal;
}

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

void MultiplyPolyNomials(const int arr1[], const int m, const int arr2[], const int n) {
  const int size = (m + n - 1);
  int result[size];
  bzero(result, sizeof(result));
  for(int i = 0; i < m; i++) {
    for(int j = 0; j < n; j++) {
      const int pos = i + j;
      result[pos] += arr1[i] * arr2[j];
    }
  }
  DisplayPolyNomial(result, size);
}

void AddPolyNomials(const int arr1[], const int m, const int arr2[], const int n) {
  const int size = (m > n) ? m : n;
  int result[size];
  bzero(result, sizeof(result));
  int i, j, k;
  for(i = 0, j = 0, k = 0; i < m && j < n; i++, j++) {
    result[k++] = arr1[i] + arr2[j];
  }
  while(i < m) {
    result[k++] = arr1[i++];
  }
  while(j < n) {
    result[k++] = arr2[j++];
  }
  DisplayPolyNomial(result, size);
}

void SubPolyNomials(const int arr1[], const int m, const int arr2[], const int n) {
  const int size = (m > n) ? m : n;
  int result[size];
  bzero(result, sizeof(result));
  int i, j, k;
  for(i = 0, j = 0, k = 0; i < m && j < n; i++, j++) {
    result[k++] = arr1[i] - arr2[j];
  }
  while(i < m) {
    result[k++] = arr1[i++];
  }
  while(j < n) {
    result[k++] = arr2[j++];
  }
  DisplayPolyNomial(result, size);
}

// ax+b = c
// a   - coeffecients
// b,c - constants
void SolveOneLinearEq(const char* equation) {
  int signVal = 1;
  bool toggle = false;
  int index, intVal, intSum, varSum;
  for(index = 0, intVal = 0, intSum = 0, varSum = 0; index < strlen(equation); index++) {
    if((equation[index] >= '0') && (equation[index] <= '9')) {
      // Extract integer number
      intVal = (intVal * 10) + (equation[index] - '0');
      if(abs(intVal)/10 == 0) {
        intVal = (signVal * intVal);
      }
    } else if(equation[index] == 'x') {
      // Consume integer number for variable coeffecient
      if(intVal != 0) {
        varSum = varSum + intVal;
      } else {
        varSum = varSum + signVal;
      }
      intVal = 0;
    } else if((equation[index] == '+')||(equation[index] == '-')) {
      // Consume integer number for total sum value
      if (intVal != 0) {
        intSum = intSum + intVal;
      }
      intVal = 0;
      // Decide sign value based on LHS or RHS
      if(toggle) {
        signVal = (equation[index] == '-') ? 1 : -1;
      } else {
        signVal = (equation[index] == '+') ? 1 : -1;
      }
    } else if(equation[index] == '=') {
      // Equal value, consume integer value for total sum value
      if(intVal != 0) {
        intSum = intSum + intVal;
      }
      // Toggle sign for RHS variables and values
      intVal = 0;
      signVal = -1;
      toggle  = true;
    }
  }
  // Equation end, consume integer value for total sum value
  if(intVal != 0) {
    intSum = intSum + intVal;
  }

  printf("\nEquation: %s", equation);
  if(varSum == 0) {
    if (intSum == 0) {
      printf("\nInfinite solutions");
    } else {
      printf("\nNo solution");
    }
  } else {
    printf("\nSolution: x = %d", ((intSum * -1) / (varSum)));
  }
}

int Find2DMatrixDeterminant(int** arr, int x, int y) {
  int val = (arr[i][i] * arr[j][j]) - (arr[i][j] * arr[j][i]);
  return 0;
}

int Find3DMatrixDeterminant(int** arr, int row, int col) {
  int value = 0;
  int sign = 1;
  for(int j = 0; j <= col; j++) {
    int temp = sign * arr[j][0];
    sign = sign * -1;
    int x = (j + 1) % col;
    int y = (x + 1) % col;
    value = value + temp * Find2DMatrixDeterminant(arr, x, y);
  }
  return value;
}

int main() {
  printf("%s", show_bool(isPerfectSquare(64)));
  return 0;
}
