/***********************************************/
/********   Basic Bitwise Problems    **********/
/* https://www.mathsisfun.com/binary-decimal-hexadecimal-converter.html */
/***********************************************/

#include <iostream>
#include <cstdio>
#include <cmath>
#define MAX_BITS      32
#define SHOW_BIT      32
#define BOOL_STR(x)   ((x)?"True":"False")
typedef unsigned int  uint_t;

// Show binary representation of number
void show_binary(const int number, const int count) {
  int binary[MAX_BITS] = {0};
  for(int index = 0; index < MAX_BITS; index++) {
    binary[index] = (number & (1 << index)) ? 1 : 0;
  }
  printf("\nValue: ");
  for(int index = (count - 1); index >=0; index--) {
    printf("\t%d", binary[index]);
  }
  printf("\nIndex: ");
  for(int index = (count - 1); index >=0; index--) {
    printf("\t%d", index);
  }
}

// Check if bit is set at position K - O(K)
bool is_set(const int number, const int position) {
  return (number & (1 << position)) ? true : false;
}

// Check if bit is clear at position K - O(K)
bool is_clear(const int number, const int position) {
  return (number & (1 << position)) ? false : true;
}

// Set bit at position K (using OR) - O(K)
int set_bit(const int number, const int position) {
  return (number | (1 << position));
}

// Clear bit at position K (using AND COMPLEMENT) - O(K)
int clear_bit(const int number, const int position) {
  return (number & ~(1 << position));
}

// Toggle bit at position K (using XOR) - O(K)
int toggle_bit(const int number, const int position) {
  return (number ^ (1 << position));
}

// Count number of set bits - O(LogN)
int count_set_bit(const int number) {
  int counter = 0;
  for(int value = number; value > 0; value = (value & (value - 1))) {
    // One bit is reset in this loop
    counter++;
  }
  return counter;
}

// Count number of cleared bits - O(LogN)
int count_clear_bit(const int number) {
  return MAX_BITS - count_set_bit(number);
}

// Count number of bits at odd position and even position - O(N)
void count_odd_even(const int number) {
  int odd = 0, even = 0;
  int value = number;
  while(value > 0) {
    if(value & 1) {
      odd++;
    }
    if(value & 2) {
      even++;
    }
    value = value >> 2;
  }
  printf("\nOdd bits set: %d", odd);
  printf("\nEven bits set: %d", even);
}

// Left rotate number by specified count of bits - O(MAX_BITS)
int left_rotate(const int number, const int count) {
  // Left shift number by count bits to OR with
  // Right shift number by Maximum bits - Count bits
  return ((number << count) | (number >> (MAX_BITS - count)));
}

// Right rotate number by specified count of bits - O(MAX_BITS)
int right_rotate(const int number, const int count) {
  return ((number >> count) | (number << (MAX_BITS - count)));
}

// Swap bits at specified positions (0 based index)
uint_t swap_bits(const uint_t number, const uint_t pos1, const uint_t pos2) {
  // Get bit at position 1
  uint_t bit1 = (number >> pos1) & 1;
  // Get bit at position 2
  uint_t bit2 = (number >> pos2) & 1;
  // XOR position bits
  uint_t sum = bit1 ^ bit2;
  // Move XORed bit to respective positions
  sum = (sum << pos1) | (sum << pos2);
  // XOR with original number for swapped bits
  return (number ^ sum);
}

// Check if number is power of 2 - O(1)
bool is_powerOf2(const int number) {
  // Ensure only 1 bit is set, which is reset by AND operation
  return ((number > 0) && ((number & (number - 1)) == 0));
}

// Check if number is power of 2 - O(1)
bool is_powerOf4(const int number) {
  // Ensure number is power of 2
  if((number > 0) && ((number & (number - 1)) == 0)) {
    // Finds position of rightmost only set bit
    int zero_count = log2(number);
    // Count number of even zeros
    return ((zero_count % 2) == 0);
  }
  return false;
}

// Find position of right most set bit - O(1)
int rightmost_set_bit(const int number) {
  // Number AND its 2's complement gives only rightmost set bit
  int value = number & (~number + 1);
  // Finds position of rightmost only set bit
  return log2(value) + 1;
}

// Valid subnet mask is 1111000 - O(1)
bool is_subnetmask(const short number) {
  // 2's complement for subnet mask gives only rightmost set bit
  int value = (~number + 1);
  // Check that only 1 bit is set
  return is_powerOf2(value);
}

int main() {
  // show_binary(INT_MAX-255, SHOW_BIT);
  //show_binary(128, SHOW_BIT);
  //printf("\nIs subnet: %s", BOOL_STR(is_subnetmask(128)));
  // show_binary(right_rotate((INT_MAX-255), 3), SHOW_BIT);
  // show_binary(left_rotate((INT_MAX-255), 3), SHOW_BIT);
  //show_binary(56, SHOW_BIT);
  //printf("\n%d", (7 << 3));
  //printf("\nIs power: %s", BOOL_STR(is_powerOf4(64)));
  // printf("\nIs set: %s", BOOL_STR(is_set(345, 8)));
  // printf("\nIs clear: %s", BOOL_STR(is_clear(345, 8)));
  // printf("\nSet count: %d", count_set_bit(345));
  // printf("\nclear count: %d", count_clear_bit(345));
  // int value1 = clear_bit(345, 5);
  // show_binary(value1, SHOW_BIT);
  // count_odd_even(345);
  // printf("\nIs Subnet: %s", BOOL_STR(is_subnetmask(56)));
  // printf("\nRightmost set: %d", rightmost_set_bit(12));
  // show_binary(176, SHOW_BIT);
  // printf("\nVal: %u", swap_bits(176, 5, 1));
  // show_binary(146, SHOW_BIT);
}
