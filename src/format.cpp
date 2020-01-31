#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
std::string Format::ElapsedTime(long numberOfSeconds) //[[maybe_unused]]) 
{
  int hh , mm , ss; 
  mm = numberOfSeconds / 60;
  hh = mm / 60;
  ss = int(numberOfSeconds % 60);
  //minutes = int(minutes % 60);
  std::string result = to_string(hh) + ":" + to_string(mm) + ":" + to_string(ss);
  return result;
}












// string Format::ElapsedTime(long seconds) {
//     int h, m, s;
//     h = seconds / 3600;
//     m = (seconds % 3600) / 60;
//     s = (seconds % 3600) % 60;
//     return (h < 10 ? "0" + to_string(h) : to_string(h))
//     + ":" + (m < 10 ? "0" + to_string(m) : to_string(m))
//     + ":" + (s < 10 ? "0" + to_string(s) : to_string(s));
// }