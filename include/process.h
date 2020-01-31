#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp     , Done: Return this process's ID    , return one (back) pid for now !!!!
  std::string User();                      // TODO: See src/process.cpp     , Done: Return the user (name) that generated this process
  std::string Command();                   // TODO: See src/process.cpp     , Done: Return the command that generated this process
  float CpuUtilization();                  // TODO: See src/process.cpp     
  std::string Ram();                       // TODO: See src/process.cpp     , Done: Return this process's memory utilization        
  long int UpTime();                       // TODO: See src/process.cpp     , Done: Return the age of this process (in seconds)
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 public:
 std::string pid_ = "1";
};

#endif