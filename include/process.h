#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid) : pid_(pid)
  {
      user_ = LinuxParser::User(pid_);
      command_ = LinuxParser::Command(pid_);
      cpuutilization_ = LinuxParser::Cpu(pid_);
      ram_ = LinuxParser::Ram(pid_);
      uptime_ = LinuxParser::UpTime(pid_);
  }

  int Pid();                               // TODO: See src/process.cpp     , Done: Return this process's ID   
  std::string User();                      // TODO: See src/process.cpp     , Done: Return the user (name) that generated this process
  std::string Command();                   // TODO: See src/process.cpp     , Done: Return the command that generated this process
  float CpuUtilization();                  // TODO: See src/process.cpp     , Done: Return this process's CPU utilization
  std::string Ram();                       // TODO: See src/process.cpp     , Done: Return this process's memory utilization        
  long int UpTime();                       // TODO: See src/process.cpp     , Done: Return the age of this process (in seconds)
  bool operator>(Process const& a) const;  // TODO: See src/process.cpp     , Done: Overload the "less than" comparison operator for Process objects

  // TODO: Declare any necessary private members
 private:
  int pid_;
  float cpuutilization_;
  std::string ram_;
  std::string user_;
  std::string command_;
  long int uptime_;
};

#endif