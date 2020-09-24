/***********************************************/
/*****   Basic Arithmetic Solutions   **********/
/***********************************************/
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "limits.h"
#include "math.h"

#define MAX_BUFF_SIZE   100000
#define show_bool(val) ((val) ? "True" : "False")

typedef unsigned long long int  ullint_t;   // 8 bytes unsigned
typedef long long int           llint_t;    // 8 bytes signed
typedef unsigned int            uint_t;     // 4 bytes unsigned

// Count number of digits
uint_t number_count_digits(const int numValue) {
  uint_t counter = 1;
  for(uint_t dividend = abs(numValue); dividend > 1; (dividend = dividend / 10)) {
    counter++;
  }
  return counter;
}

// Extract digit at specific position
uint_t number_digit_position(const int numValue, const uint_t digitPos) {
  const uint_t absNumber = abs(numValue);
  const uint_t digitsCnt = floor(log10(absNumber)) + 1;
  if(digitPos <= digitsCnt) {
    const uint_t factorPos = pow(10, (digitsCnt - digitPos));
    return (absNumber / factorPos) % 10;
  }
  return UINT_MAX;
}

// Valid if input number is power of another number
bool number_check_power(const int numValue, const int powFactor) {
  bool retValue = false;
  if((powFactor == 0)||(numValue == 0)) {
    // Zero power 0 or any number is not defined
    retValue = false;
  } else if (powFactor == 1) {
    // Any non-zero number is power of 1
    retValue = (numValue != 0);
  } else {
    int tmpValue;
    for(tmpValue = numValue; tmpValue > powFactor; (tmpValue = tmpValue / powFactor));
    retValue = (tmpValue == powFactor);
  }
  return retValue;
}

// Check if number is perfect square
bool is_perfect_square(const uint_t numVal) {
  uint_t index;
  for(index = 1; (index * index) < numVal; index++);
  return ((index * index) == numVal);
}

// Display fiboanacci series with specific count
void display_fibonnaci_series(const uint_t numCount) {
  uint_t sequence[numCount + 1];
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

// Get Nth term of fibonacci series
uint_t get_fibonacci_term(const uint_t numCount) {
  if (numCount > 2) {
    return get_fibonacci_term(numCount - 1) +
           get_fibonacci_term(numCount - 2);
  }
  return (numCount == 1) ? 0 : 1;
}

// Get next value of fibonacci series
uint_t get_fibonacci_next(const uint_t numCount) {
  // Next-Number = Given-Number * Golden ratio [1+sqrt(5)]/2
  uint_t nextValue = round(numCount * ((1 + sqrt(5)) / 2));
  return nextValue;
}

// Check if given number is valid fibonacci
bool is_valid_fibonacci(const uint_t numValue) {
  // Check isf (5N2 + 4) or (5N2 - 4) is perfect square
  ullint_t baseVal = 5 * (numValue * numValue);
  return is_perfect_square(baseVal - 4) || is_perfect_square(baseVal + 4);
}

// Display prime numbers below specific number
void display_prime_numbers(const uint_t numValue) {
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
    // Compute next values (6N - 1) and (6N + 1)
    const uint_t tmpValue = 6 * counter;
    lower = tmpValue - 1;
    upper = tmpValue + 1;
  }
}

// Check if given number is valid prime number
bool is_valid_prime(const int numValue) {
  // All numbers less than 2 and even numbers are not prime
  if((numValue <= 1)||(numValue % 2 == 0)) {
    // Only 2 is even prime number
    return (numValue == 2) ? true : false;
  } else {
    // Iterate over sqrt(N) to find factors
    for(int index = 2; (index * index) <= numValue; index++) {
      if(numValue % index == 0) {
        return false;
      }
    }
  }
  return true;
}

// Find factorial of given number
ullint_t get_factorial_result(const ullint_t numValue) {
  if (numValue > 1) {
    return numValue * get_factorial_result(numValue - 1);
  }
  return 1;
}

// Get square root of given number
double get_square_root(const double numberVal) {
  const double precision = 0.000001;
  double resultVal;
  // Integer calculation
  for (resultVal = 1; resultVal * resultVal <= numberVal; resultVal++);
  // Fraction calculation
  for (--resultVal; resultVal * resultVal < numberVal; resultVal += precision);
  return resultVal;
}

// Get Nth root of given number
double get_nfactor_root(const double numberVal, const double rootVal) {
  const double precision = 0.000001;
  double resultVal;
  // Integer calculation
  for (resultVal = 1; pow(resultVal, rootVal) <= numberVal; resultVal++);
  // Fraction calculation
  for (--resultVal; pow(resultVal, rootVal) < numberVal; resultVal += precision);
  return resultVal;
}

// Multiply each digit of result array with base number
int multiply_result_array(int* result, const int size, const int base) {
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

// Find power of base number with very large result
void number_large_power(const int base, const int power) {
  int arrResult[MAX_BUFF_SIZE];
  int resultSize = 0;
  if (base == 0) {
    // power of 0 is undefined
    arrResult[resultSize++] = 0;
  } else if (power == 0) {
    // 0th power of any number is 1
    arrResult[resultSize++] = 1;
  } else {
    // Compute using absolute value
    int absval = abs(base);
    // Initialize result array
    for(int value = absval; value != 0; value = value / 10) {
      arrResult[resultSize] = value % 10;
      resultSize ++;
    }
    // Multiply number by itself (power times)
    for(int index = 1; index < power; index ++) {
      resultSize = multiply_result_array(arrResult, resultSize, absval);
    }
  }
  // If base number is negative, then odd power will give negative result
  const char signChar = ((base < 0) && (power % 2 != 0)) ? '-' : '+';
  printf("\n%d^%d gives %d-digit result: %c",
    base, power, resultSize, signChar);
  // Display final result
  for (int index = (resultSize - 1); index >= 0; index--) {
    printf("%d", arrResult[index]);
  }
}

int main () {
  //display_prime_numbers(10);
  number_large_power(232232, 12);
  //printf("%s", show_bool(is_valid_prime(11)));
}
