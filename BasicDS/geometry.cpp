/***********************************************/
/********   Basic Geometry Problems   **********/
/***********************************************/
#include <iostream>

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

int main() {
  clock_angle(3, 30);
  return 0;
}
