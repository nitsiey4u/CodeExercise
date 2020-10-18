/***********************************************/
/********   Basic Geometry Problems   **********/
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

// Comparator
int comparator(const void* a, const void *b) {
  return (*(int*)a - *(int*)b);
}

void display_array(const char* hdr, int arr[], int size) {
  printf("\n%s: ", hdr);
  for(int index = 0; index < size; index++) {
    printf("\t%d", arr[index]);
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
  return angle_diff;
}


// Possible triangles from given array - O(N2)
// a + b > c (Sum of any two sides greater than 3rd side)
void possible_triangles(int arr[], const int size) {
  int counter = 0;
  qsort(arr, size, sizeof(int), comparator);
  // Iterate over sorted list - O(N)
  for(int outer = (size - 1); outer >=2; outer--) {
    // Rightmost value saved as fixed larger side
    int lower = 0;
    int upper = outer - 1;
    int large_sum = arr[outer];
    // Iterate over sorted list to find smaller sides - O(N)
    while(lower < upper) {
      // Sum of lower and upper sides > larger side
      int sides_sum = arr[lower] + arr[upper];
      // Triangle can be formed from smallest value
      if(sides_sum > large_sum) {
        // (Upper - Lower) triangles possible
        for(int inner = lower; inner < upper; inner++) {
          counter++;
          printf("\n%d. Triangle:\t%d\t%d\t%d",
                counter, arr[inner], arr[upper], arr[outer]);
        } // End of inner loop
        // The upper side is addressed decrement backward
        upper --;
      } else {
        // The lower side is too small increment forward
        lower ++;
      }
    } // End of outer loop
  }
}

int main() {
  // clock_angle(3, 30);

  //int arr[] = {4, 3, 5, 7, 6};
  int arr[] = {2, 3, 9, 10, 12, 15};
  int size  = sizeof(arr)/sizeof(arr[0]);
  display_array("Array", arr, size);
  possible_triangles(arr, size);
  return 0;
}
