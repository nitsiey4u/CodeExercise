/***********************************************/
/*********** General Basic Problems	 ***********/
/***********************************************/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <queue>

using namespace std;

// Predefined constants
#define MAX_BUFF_SIZE   100000
#define MAX_TEMP_SIZE		256
#define MAX_CHAR_SIZE   80
#define MAX_JUMP_SIZE   9
#define show_bool(val)  ((val) ? "True" : "False")

typedef unsigned long long int  ullint_t;   // 8 bytes unsigned
typedef long long int           llint_t;    // 8 bytes signed
typedef unsigned int            uint_t;     // 4 bytes unsigned

// Comparator
int comparator(const void* a, const void *b) {
  return (*(int*)a - *(int*)b);
}

// Swapper (Constant pointer)
void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// Helper to display array
void display_array(const char* hdr, int arr[], int size) {
  printf("\n%s: ", hdr);
  for(int index = 0; index < size; index++) {
    printf("\t%d", arr[index]);
  }
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

//  Given array of values, insert product of remaining values - O(N)
void array_product(int values[], int product[], int size) {
  int zero_count    = 0;
  int total_product = 1;
  // Count number of zeroes and total product of all numbers
  for(int index = 0; (index < size) && (zero_count < 2); index++) {
    if(values[index] == 0) {
      zero_count++;
    } else {
      total_product = total_product * values[index];
    }
  }
  printf("\nTotal Product: %d", total_product);
  // Iterate to fill over product values
  for(int index = 0; index < size ; index++) {
    // If values has only 1 zero
    if(zero_count == 1) {
      // If value[index] is 0, use total_product else 0
      product[index] = (values[index] == 0)? total_product : 0;
    }
    // If values had 2 zeroes
    else if (zero_count == 2) {
      // All product values will be 0
      product[index] = 0;
    }
    // If values has no zeroes
    else {
      // Divide total product by value[index] which needs to be ignored
      product[index] = total_product / values[index];
    }
  }
}

// Find pairs of value with matching sum - O(NlogN)
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

// Find pairs of value with matching sum using hashtable - O(N)
void hash_pairs(int arr[], int size, const int sum) {
  unordered_set<int> hashset;
  for(int index = 0; index < size; index++) {
    int value = sum - arr[index];
    if(hashset.find(value) != hashset.end()) {
      printf("\nSum pair: %d and %d", arr[index], value);
    }
    hashset.insert(arr[index]);
  }
}

// Get rightmost set bit of number
int rightmost_set_bit(const int number) {
  // Number AND (2's complement of Number gives rightmost set bit)
  int result = number & (~number + 1);
  // Logarithm of result gives 0 based index position
  return log2(result);
}

// Check if bit is set at rightmost position
bool is_bit_set(const int number, const int position) {
  return ((number >> position) & 1);
}

// Given array of distinct values, find 1 missing number - O(N)
// Count of natural numbers provided as reference
int missing_one_number(int arr[], int size, int lower, int upper) {
  // Find XOR of expected elements
  int exp_value = 0;
  for(int index = lower; index <= upper; index++) {
    exp_value = exp_value ^ index;
  }
  //printf("\nExpected: %d", exp_value);
  // Find XOR of array elements
  int arr_value = 0;
  for(int index = 0; index < size; index++) {
    arr_value = arr_value ^ arr[index];
  }
  //printf("\nActual: %d", arr_value);
  return exp_value ^ arr_value;
}

// Given array of distinct values, find 2 missing numbers - O(N)
// Count of natural numbers provided as reference
void missing_two_numbers(int arr[], int size, int count) {
  // XOR for missing numbers
  int xor_missing = missing_one_number(arr, size, 1, count);
  printf("\nMissing: %d", xor_missing);

  int pos_bitset  = rightmost_set_bit(xor_missing);
  printf("\nBit Set: %d", pos_bitset);

  // Get XOR of expected numbers
  int exp_value = 0;
  for(int index = 1; index <= count; index++) {
    if(is_bit_set(index, pos_bitset)) {
      printf("\nIndex %d has rightmost bit set", index);
      exp_value = exp_value ^ index;
    }
  }
  // Get XOR of array elements
  int arr_value = 0;
  for(int index = 0; index < size; index++) {
    if(is_bit_set(arr[index], pos_bitset)) {
      printf("\nValue %d has rightmost bit set", arr[index]);
      arr_value = arr_value ^ arr[index];
    }
  }
  // First missing value
  int one_missing = exp_value ^ arr_value;
  int two_missing = xor_missing ^ one_missing;
  printf("\nMissing numbers: %d and %d", one_missing, two_missing);
}

// Given array of values, find repeating and missing numbers - O(N)
// Count of natural numbers provided as reference
void repeating_missing(int arr[], const int size, const int count) {
  int xor_numbers = missing_one_number(arr, size, 1, count);
  int pos_setbit  = rightmost_set_bit(xor_numbers);
  // For missing number
  int exp_value = 0;
  for(int index = 1; index <= count; index++) {
    if(is_bit_set(index, pos_setbit)) {
      //printf("\nIndex %d has rightmost bit set", index);
      exp_value = exp_value ^ index;
    }
  }
  // For repeating numbers
  int arr_value = 0;
  for(int index = 0; index < size; index ++) {
    if(is_bit_set(arr[index], pos_setbit)) {
      //printf("\nValue %d has rightmost bit set", arr[index]);
      arr_value = arr_value ^ arr[index];
    }
  }
  // Find exact numbers
  int missing_number   = exp_value ^ arr_value;
  int repeating_number = xor_numbers ^ missing_number;
  printf("\nMissing number: %d", missing_number);
  printf("\nRepeating number: %d", repeating_number);
}

// Given array of values, find UNIQUE numbers - O(N)
void distinct_elements(int arr[], const int size) {
  int xor_value = 0;
  for(int index = 0; index < size; index++) {
    xor_value = xor_value ^ arr[index];
  }
  int bit_position = rightmost_set_bit(xor_value);
  printf("\nXOR Sum: %d Position: %d", xor_value, bit_position);
  int xValue = 0;
  int yValue = 0;
  // Partition array into matching and non-matching halves
  for(int index = 0; index < size; index++) {
    if(is_bit_set(arr[index], bit_position)) {
      xValue = xValue ^ arr[index];
    } else {
      yValue = yValue ^ arr[index];
    }
  }
  printf("\nDistinct elements: %d and %d", xValue, yValue);
}

// Given array of values, find REPETITIVE numbers - O(N)
// Count of natural numbers provided as reference
void repeating_elements(int arr[], const int size, const int count) {
  int exp_value = 0;
  for(int index = 1; index <= count; index++) {
    exp_value = exp_value ^ index;
  }
  int arr_value = 0;
  for(int index = 0; index < size; index++) {
    arr_value = arr_value ^ arr[index];
  }
  // XOR of repetitive values
  int xor_sum = exp_value ^ arr_value;
  int bit_pos = rightmost_set_bit(xor_sum);
  printf("\nXOR Sum: %d Position: %d", xor_sum, bit_pos);
  // XOR all elements with same bit set position from expected values
  int xor_value = 0;
  for(int index = 1; index <= count; index++) {
    if(is_bit_set(index, bit_pos)) {
      xor_value = xor_value ^ index;
    }
  }
  // XOR all elements with same bit set position from array values
  for(int index = 0; index < size; index++) {
    if(is_bit_set(arr[index], bit_pos)) {
      xor_value = xor_value ^ arr[index];
    }
  }
  int xValue = xor_value;
  int yValue = xor_sum ^ xor_value;
  printf("\nRepeating elements: %d and %d", xValue, yValue);
}

// Given sorted array of values, rearrange max min order - O(NLogN)
// Example: [1, 2, 3, 4, 5, 6, 7] => [7, 1, 6, 2, 5, 3, 4]
void maxmin_rearrange(int arr[], const int size) {
  // Swap/Sort while iterating over array
  for(int index = 0; index < size; index++) {
   // Swap (to get largest numbers), Sort (to get smallest numbers)
   if((index % 2) == 0) {
     // Swap even position value with smallest element at end
     swap(&arr[index], &arr[size - 1]);
   } else {
     // Sort right array (size - index) upto last element
     qsort(&arr[index], (size - index), sizeof(int), comparator);
   }
  }
}

// Find triplets matching sum using hashtable - O(N2)
void sum_triplets(int arr[], int size, const int sum) {
  // Iterate over outer loop to fix one value - O(N)
  for(int outer = 0; outer < (size - 2); outer++) {
    // Fix 1 element of triplet
    int match_sum = sum - arr[outer];
    // Space complexity - O(N)
    unordered_set<int> hashset;
    // Iterate over inner loop to find matching sum pairs - O(N)
    for(int inner = (outer + 1); inner < size; inner++) {
      int remainder = match_sum - arr[inner];
      // Find remaining 2 and 3 elements of triplet
      if(hashset.find(remainder) != hashset.end()) {
        printf("\nFound triplet:\t%d\t%d\t%d",
              arr[outer], arr[inner], remainder);
      }
      hashset.insert(arr[inner]);
    }
  }
}

// Find triplets matching sum using pointers - O(N2)
void find_triplets(int arr[], int size, const int sum) {
  // Sort array elements - O(LogN)
  qsort(arr, size, sizeof(int), comparator);
  // Outer loop over array elements - O(N)
  for(int outer = 0; outer < (size - 2); outer++) {
    int match_sum = sum - arr[outer];
    int lower = outer + 1;
    int upper = (size - 1);
    // Inner loop over array elements - O(N)
    while(lower < upper) {
      int value_sum = arr[lower] + arr[upper];
      if(value_sum == match_sum) {
        printf("\nFound triplet:\t%d\t%d\t%d",
              arr[outer], arr[lower], arr[upper]);
        lower ++;
        upper --;
      } else if (value_sum < match_sum) {
        lower ++;
      } else {
        upper --;
      }
    }
  }
}

// Find pythagoras triplet using pointers - O(N2)
void pythagoras_triplets(int arr[], int size) {
  // Iterate over array elements to square each element - O(N)
  for(int index = 0; index < size; index++) {
    arr[index] = arr[index] * arr[index];
  }
  // Sort squared elements of array - O(N2)
  qsort(arr, size, sizeof(int), comparator);
  // Iterate from largest value to smallest - O(N)
  for(int index = (size - 1); index >= 2; index --) {
    int lower = 0;
    int upper = (index - 1);
    int match_sum = arr[index];
    // Iterate over matching values - O(N)
    while (lower < upper) {
      int value_sum = arr[lower] + arr[upper];
      if(value_sum == match_sum) {
        printf("\nFound triplet:\t%d\t%d\t%d",
          (int)sqrt(arr[lower]), (int)sqrt(arr[upper]), (int)sqrt(arr[index]));
        lower ++;
        upper --;
      } else if(value_sum < match_sum) {
        lower ++;
      } else {
        upper --;
      }
    }
  }
}

// Generate jumping numbers - O(K), K numbers smaller than MAX
void jumping_numbers(const int maxval) {
  bool flag = true;
  printf("\n0");
  // Array of queue for 9 digits (1...9), ignore 0 digit
  queue<int> JUMPQ[MAX_JUMP_SIZE];
  for(int index = 0; index < MAX_JUMP_SIZE; index++) {
    // Store each counting number (1..9) into respective queue
    JUMPQ[index].push(index + 1);
  }
  // Iterate over array of queues until max value is reached
  for(int index = 0; (index < MAX_JUMP_SIZE) && (flag);
      index = (index + 1) % MAX_JUMP_SIZE) {
    // Number of elements in queue to be processed
    int counter = JUMPQ[index].size();
    while(counter > 0) {
      // For each element find lower and upper numbers
      int value = JUMPQ[index].front();
      JUMPQ[index].pop();
      if(value > maxval) {
        flag = false;
        break;
      }

      // Display popped number from front
      printf("\n%d", value);
      //printf("\nPop: %d", value);

      // Get last digit of number, push generated lower/upper number
      int digit = value % 10;

      // If digit is 0, lower value cannot be obtained
      // Example: Number(10) => Only Upper Value (101)
      if(digit != 0) {
        int lower = value * 10 + (digit - 1);
        //printf("\nPush lower: %d", lower);
        JUMPQ[index].push(lower);
      }

      // If digit is 0, upper value cannot be obtained
      // Example: Number(9) => Only Lower Value (98)
      if(digit != 9) {
        int upper = value * 10 + (digit + 1);
        //printf("\nPush upper: %d", upper);
        JUMPQ[index].push(upper);
      }

      // We have generated lower/upper from popped number, decrement counter
      counter --;
    } // End of inner while loop
  } // End of outer for loop
}

int main(int argc, char* argv[]) {
	// int arr[] = {1, 5, 7, -1, 5};
  // int size  = sizeof(arr)/sizeof(arr[0]);
  // display_array("Display", arr, size);
  // int arr[] = {0, 4, 45, 6, 10, 8};
  // int size  = sizeof(arr)/sizeof(arr[0]);
  // display_array("Display", arr, size);
  // find_triplets(arr, size, 18);

  // int arr[] = {3, 1, 4, 6, 5};
  // int size  = sizeof(arr)/sizeof(arr[0]);
  // display_array("Display", arr, size);
  // pythagoras_triplets(arr, size);

  // sum_pairs(arr, size, 6);
  // hash_pairs(arr, size, 6);
  // int arr[]  = {9, 6, 3, 4, 5, 7, 4};
  // int size   = sizeof(arr)/sizeof(arr[0]);
  // int minima = local_minima(arr, 0, (size - 1), (size - 1));
  // printf("\nLocal Minima: %d (Value: %d)", minima, arr[minima]);
  // int maxima = local_maxima(arr, 0, (size - 1), (size - 1));
  // printf("\nLocal Maxima: %d (Value: %d)", maxima, arr[maxima]);

  // int values[] = {1, 3, 5, 6};
  // int size     = sizeof(values)/sizeof(values[0]);
  // int result[size];
  // display_array("Values", values, size);
  // array_product(values, result, size);
  // display_array("Result", result, size);
  // missing_numbers(values, size, 6);

  // int arr[] = {1, 2, 4, 6, 7, 8, 9};
  // int size  = sizeof(arr)/sizeof(arr[0]);
  // printf("\nMissing: %d", missing_one_number(arr, size, 1, 5));
  // missing_two_numbers(arr, size, 9);

  // int arr[] = {4, 3, 6, 2, 1, 1};
  // int size  = sizeof(arr)/sizeof(arr[0]);
  // repeating_missing(arr, size, size);

  // int arr[] = {2, 2, 4, 5, 6, 5, 9, 9};
  // int size  = sizeof(arr)/sizeof(arr[0]);
  // distinct_elements(arr, size);

  // int arr[] = {1, 2, 3, 4, 1, 2};
  // int size  = sizeof(arr)/sizeof(arr[0]);
  // distinct_elements(arr, size);
  // repeating_elements(arr, size, 4);

  // int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  // int size  = sizeof(arr)/sizeof(arr[0]);
  // display_array("Sorted", arr, size);
  // maxmin_rearrange(arr, size);
  //
  // display_array("Display", arr, size);
  jumping_numbers(100);
	return 0;
}
