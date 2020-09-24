/***********************************************/
/*********** General String Problems	 ***********/
/***********************************************/
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "limits.h"
#include "math.h"

// Predefined constants
#define MAX_BUFF_SIZE   100000
#define show_bool(val)  ((val) ? "True" : "False")

typedef unsigned long long int  ullint_t;   // 8 bytes unsigned
typedef long long int           llint_t;    // 8 bytes signed
typedef unsigned int            uint_t;     // 4 bytes unsigned

// Converts String to Integer (MSB to LSB) -->
llint_t string_to_integer(const char* strValue) {
  llint_t intValue = 0;
	// Check for positive/negative sign
  const int signFlag = (strValue[0] == '-') ? -1 : 1;
	// Define limit if sign is passed with number
  const int limitPos = ((strValue[0] == '-') || (strValue[0] == '+')) ? 1 : 0;
	// Parse string left to right for processing each digit
  for (int indexPos = limitPos; indexPos < strlen(strValue); indexPos++) {
    uint_t posval = strValue[indexPos] - '0';
    intValue = (intValue * 10) + posval;
  }
	// Return with exact sign value
  return intValue * signFlag;
}

// Converts String to Integer Reverse (LSB to MSB) <--
llint_t string_to_integer_reverse(const char* strValue) {
  llint_t intValue = 0;
	// Check for positive/negative sign
  const int signFlag = (strValue[0] == '-') ? -1 : 1;
	// Define limit if sign is passed with number
  const int limitPos = ((strValue[0] == '-') || (strValue[0] == '+')) ? 1 : 0;
	uint_t factorPos = 1;
	// Parse string right to left for processing each digit
	for(int indexPos = (strlen(strValue) - 1); indexPos >= limitPos; indexPos--) {
		uint_t posval = (strValue[indexPos] - '0');
		intValue = intValue + factorPos * posval;
		factorPos = factorPos * 10;
	}
	// Return with exact sign value
  return intValue * signFlag;
}

// Converts signed integer to string
void integer_to_string(const int numValue) {
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

// String convert case of all characters
void string_convert_case(const char *strVal) {
  int length = strlen(strVal);
  char resVal[length + 1];
  for(int index = 0; index < length; index++) {
    const char chVal = strVal[index];
    if(('a' <= chVal) && (chVal <= 'z')) {
      resVal[index] = 'A' + (chVal - 'a');
    } else {
      resVal[index] = 'a' + (chVal - 'A');
    }
  }
  resVal[length] = '\0';
  printf("\nInput  = %s", strVal);
  printf("\nResult = %s", resVal);
}

int main() {
  return 0;
}
