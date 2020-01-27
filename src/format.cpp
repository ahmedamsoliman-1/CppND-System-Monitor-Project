#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds[[maybe_unused]]) 
{
    //10800
    int hh;
    int mm;
    int ss;

    hh = seconds / 3600;
    mm = seconds / 60;
    ss = seconds % 60;
}
//{ return string(); }