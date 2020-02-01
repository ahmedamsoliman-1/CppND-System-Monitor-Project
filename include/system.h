#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  Processor& Cpu();                   // TODO: See src/system.cpp         // Done: Return the system's CPU
  std::vector<Process>& Processes();  // TODO: See src/system.cpp         // Done: Return a container composed of the system's processes
  float MemoryUtilization();          // TODO: See src/system.cpp         // Done: Return Return the system's memory utilization
  long UpTime();                      // TODO: See src/system.cpp         // Done: Return the number of seconds since the system started running
  int TotalProcesses();               // TODO: See src/system.cpp         // Done: Return the total number of processes on the system
  int RunningProcesses();             // TODO: See src/system.cpp         // Done: Return the number of processes actively running on the system
  std::string Kernel();               // TODO: See src/system.cpp         // Done: Return the system's kernel identifier (string)
  std::string OperatingSystem();      // TODO: See src/system.cpp         // Done: Return the operating system name

  // TODO: Define any necessary private members
 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
};

#endif