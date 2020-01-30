#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
std::string Format::ElapsedTime(long numberOfSeconds) //[[maybe_unused]]) 
{
  long hh , mm , ss; 
  mm = numberOfSeconds / 60;
  hh = mm / 60;
  ss = int(numberOfSeconds % 60);
  //minutes = int(minutes % 60);
  std::string result = std::to_string(hh) + ":" + std::to_string(mm) + ":" + std::to_string(ss);
  return result;
}