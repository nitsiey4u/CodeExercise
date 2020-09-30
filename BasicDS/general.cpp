/***********************************************/
/*********** General Basic Problems	 ***********/
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

// Comparator
int comparator(const void* a, const void *b) {
  return (*(int*)a - *(int*)b);
}

// Validate constant pointer and pointer to constant
void validate_constant_pointer() {
	int val1 = 10;
	int val2 = 20;
	printf("\nPointer to constant value - 10");
	const int* ptr1 = &val1;
	printf("\nBefore %d", *ptr1);
	printf("\nValue updated by variable - 11");
	val1 = 11;
	printf("\nAfter %d", *ptr1);
	ptr1 = &val2;
	printf("\nPointer to constant value - 20");
	printf("\nNext %d", *ptr1);

	printf("\nConstant pointer to value - 10");
	int* const ptr2 = &val1;
	printf("\nBefore %d", *ptr2);
	val1 = 15;
	printf("\nValue updated by pointer - 15");
	printf("\nAfter %d", *ptr2);
}

// Print multibyte data to check direction of endianness
void print_multibyte_data() {
	unsigned int data_value = 0x12345678;
	printf("\nActual value:%.2x", data_value);
	const char* byte_val = (char*)&data_value;
	const int byte_count = sizeof(data_value);
	printf("\nStored:");
	for(int index = 0; index < byte_count; index++) {
		printf("\t\t\t%.2x", byte_val[index]);
	}
	printf("\nAddress:");
	for(int index = 0; index < byte_count; index++) {
		printf("\t%p", &byte_val[index]);
	}
}

// Check if system is little endian or big endian
void little_big_endian() {
	// For 2 byte value, type cast to read 1 byte using char*
	short int value = 0x00FF;
	char* byte = (char*)&value;
	if(byte[0]) {
		// LSB '0xFF' at lower address - little endian
		printf("\nLittle endian");
	} else {
		// MSB '0x00' at lower address - big endian
		printf("\nBig endian");
	}

	short int word = 0x1234;
	if((*((char*)&word) & word) == 0x34) {
		printf("\nLittle endian");
	} else {
		printf("\nBig endian");
	}
}

// Check direction of stack (downwards or upwards)
void check_stack_direction(int* caller_addr) {
	int func_temp = 22;
	int* callee_addr = &func_temp;
	printf("\nCaller Address (Main): %p", caller_addr);
	printf("\nCallee Address (This): %p", callee_addr);
	//  main function (caller) --> this function (callee)
	if(caller_addr > callee_addr) {
		// If address of Main > This = stack grows downwards
		printf("\nStack grows downwards");
	} else
	{
		// If address of Main < This = stack grows upwards
		printf("\nStack grows upwards");
	}
}

// Structure to hold roman numerals
struct RomanVal {
	int 	decimal;
	char  roman[4];
};
typedef struct RomanVal ROMANVAL;

// Map of roman numerals (decimal values to roman characters)
ROMANVAL mapDecimalToRoman[] = {
	{1,			"I"		},
	{4,			"IV"	},	// <-- Negative assignment
	{5,			"V"		},
	{9,			"IX"	},	// <-- Negative assignment
	{10,		"X"		},
	{40,		"XL"	},	// <-- Negative assignment
	{50,		"L"		},
	{90,		"XC"	},	// <-- Negative assignment
	{100,		"C"		},
	{400,		"CD"	},	// <-- Negative assignment
	{500,		"D"		},
	{900,		"CM"	},	// <-- Negative assignment
	{1000,	"M"		},
};

//  Convert decimal number to roman numeral
void decimal_to_roman(const int decimal) {
	char roman[MAX_TEMP_SIZE];
	memset(roman, '\0', sizeof(roman));
	int baseIndex = (sizeof(mapDecimalToRoman)/sizeof(ROMANVAL)) - 1;
	for(int numeric = decimal; numeric > 0; baseIndex--) {
		// Get left part quotient (MSB)
		int quotient = numeric / mapDecimalToRoman[baseIndex].decimal;
		// Get right part stripping quotient (MSB)
		numeric = numeric % mapDecimalToRoman[baseIndex].decimal;
		// If quotient > 0, means decimal is divisible by max base
		for(int counter = 0; counter < quotient; counter++) {
			snprintf(roman, sizeof(roman), "%s%s",
							 roman, mapDecimalToRoman[baseIndex].roman);
		}
	}
	printf("\nDecimal = %d \nRoman = %s", decimal, roman);
}

// Parse roman character to get decimal value (postive assignments)
int getRomanToDecimal(const char roman) {
	int decimal;
	switch(roman) {
		case 'I':	decimal = 1;
		break;
		case 'V':	decimal = 5;
		break;
		case 'X':	decimal = 10;
		break;
		case 'L':	decimal = 50;
		break;
		case 'C':	decimal = 100;
		break;
		case 'D':	decimal = 500;
		break;
		case 'M':	decimal = 1000;
		break;
		default:	decimal = 0;
		break;
	}
	return decimal;
}

//  Convert roman numeral to decimal number
void roman_to_decimal(const char* roman) {
	int decimal = 0;
	for(int index = 0; index < strlen(roman); index++) {
		// Get current roman char to decimal value
		const int currval = getRomanToDecimal(roman[index]);
		if((index + 1) < strlen(roman)) {
			// Get next roman char to decimal value
			const int nextval = getRomanToDecimal(roman[index+1]);
			// Always current value is greater than next value
			if(currval >= nextval) {
				// Postive assignments
				decimal = decimal + currval;
			} else {
				// negative assignments
				decimal = decimal + (nextval - currval);
				// Increment pointer as next roman char is processed
				index ++;
			}
		} else {
				// Postive assignment for last roman char of string
				decimal = decimal + currval;
		}
	}
	printf("\nRoman = %s \nDecimal = %d", roman, decimal);
}

// Hex characters map
const char HEXMAP[] = {'A', 'B', 'C', 'D', 'E', 'F'};

// Helper for reversing string
void stringReverse(char* buffer) {
	char *strPtr, *endPtr;
	for(strPtr = buffer, endPtr = (buffer + (strlen(buffer) - 1));
			(strPtr && endPtr) && (strPtr < endPtr); strPtr++, endPtr--) {
		char temp = *strPtr;
		*strPtr = *endPtr;
		*endPtr = temp;
	}
}

// Convert decimal number to binary/octal/hex (defined by base)
void decimal_to_base(const int decimal, const int base) {
	char value[MAX_BUFF_SIZE];
	bzero(value, sizeof(value));
	int numeric, index;
	for(numeric = decimal, index = 0; numeric > 0; index++) {
		// Save remainder into value output
		int remainder = numeric % base;
		if((base == 16) && (remainder >= 10)) {
			value[index] = HEXMAP[remainder - 10];
		} else {
			value[index] = '0' + remainder;
		}
		// For next iteration, process with quotient
		numeric = numeric / base;
	}
	// Reverse value
	stringReverse(value);
	printf("\nDecimal = %d \tBase = %d", decimal, base);
	printf("\nOutput Value = %s", value);
}

// Convert binary/octal/hex value (defined by base) to decimal
void base_to_decimal(const char* value, const int base) {
	char numeral[strlen(value) + 1];
	snprintf(numeral, sizeof(numeral), "%s", value);
	stringReverse(numeral);
	int power = 1;
	int decimal = 0;
	for(int index = 0; index < strlen(numeral); index++) {
		const char posval = numeral[index];
		int intval;
		if((base == 16) && (posval >= 'A')) {
			// For hex char get corresponding integer value
			intval =  10 + (posval - 'A');
		} else {
			// For other char convert ascii to integer value
			intval = posval - '0';
		}
		// multiply base power to integer value
		decimal = decimal + (power * intval);
		// increment power for next iteration
		power = power * base;
	}
	printf("\nValue = %s \tBase = %d", value, base);
	printf("\nDecimal Output = %d", decimal);
}

// Find pairs of value with matching sum
void sum_pairs(int arr[], int size, const int sum) {
	qsort(arr, size, sizeof(int), comparator);
  int low  = 0;
  int high = size - 1;
  int count = 0;
  while(low < high) {
    if((arr[low] + arr[high]) == sum) {
      printf("\nFound pair: (%d %d)", arr[low], arr[high]);
      high --;
      low ++;
      count ++;
    } else if((arr[low] + arr[high]) > sum) {
      high --;
    }
    else {
      low ++;
    }
  }
}

int main(int argc, char* argv[]) {
	// int arr[] = {1, 5, 7, -1, 5};
  // int size  = sizeof(arr)/sizeof(arr[0]);
  // sum_pairs(arr, size, 6);
	return 0;
}
