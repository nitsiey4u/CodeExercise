#include <iostream>
#include <vector>
#include "stdlib.h"

#define MIN(x,y) ((x < y)?(x):(y))

// Comparator
int comparator(const void* a, const void *b) {
  return (*(int*)a - *(int*)b);
}

// Find pairs of value with matching sum
void sum_pairs(int arr[], int size, const int sum) {
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

// Angle between hour and min hands
int clock_angle(int hour, int minute) {
  // Ensure hour is less than 12
  if(hour > 12) {
    hour = hour - 12;
  }
  // Ensure minutes is less than 60
  if(minute > 60) {
    hour   = hour + minute/60;
    minute = minute % 60;
  }
  // Hour angle
  double hour_angle = (hour * 60 + minute) * 0.5;
  // Minutes angle
  double minute_angle = minute * 6;
  // Angle difference
  int angle_diff = abs(hour_angle - minute_angle);
  // Consider shorter angle and return it
  angle_diff = (angle_diff > 180)? 360 - angle_diff : angle_diff;
  printf("\nTime: %d:%d Clock Angle: %d", hour, minute, angle_diff);
  return 0;
}

int main() {
  int arr[] = {1, 5, 7, -1, 5};
  int size  = sizeof(arr)/sizeof(arr[0]);
  qsort(arr, size, sizeof(int), comparator);
  sum_pairs(arr, size, 6);
  return 0;
}
