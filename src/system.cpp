#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() 
{
    std::string linuxKernal(LinuxParser::Kernel());
    return linuxKernal;
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() 
{
    float memoryUtilization = LinuxParser::MemoryUtilization();
    return memoryUtilization;
}

// TODO: Return the operating system name
std::string System::OperatingSystem() 
{
    std::string linuxOperatingSystem = LinuxParser::OperatingSystem();
    return linuxOperatingSystem;
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() 
{
    int runningProcesses = LinuxParser::RunningProcesses();
    return runningProcesses;
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() 
{
    int totalProcesses = LinuxParser::TotalProcesses();
    return totalProcesses;
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() 
{
    long int linuxUpTime = LinuxParser::UpTime();
    return linuxUpTime;
}