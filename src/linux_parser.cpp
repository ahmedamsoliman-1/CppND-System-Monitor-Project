#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{
  float MemTotal, MemFree, Buffers, Cached;
  string line;
  string key;
  string memvalue;
  string kb;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      (linestream >> key >> memvalue>>kb);
      
        if (key == "MemTotal:") { MemTotal = stof(memvalue); }
        else if (key == "MemFree:") { MemFree = stof(memvalue); }
        else if (key == "Buffers:") { Buffers = stof(memvalue); } 
        else if (key == "Cached:") { Cached = stof(memvalue); }
      
      }
    }
return (MemTotal - (MemFree + Buffers + Cached)) / MemTotal;
 // return MemoryUtilization;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() 
{
  long uptime_system, uptime_idle;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime_system >> uptime_idle;
  }
  return uptime_system;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() 
{
  return ActiveJiffies() + IdleJiffies();
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) //[[maybe_unused]]) { return 0; }
{
    string line, value;
  long totalTime, utime, stime, cutime, cstime;
  int const offset = 1;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    getline(filestream, line);
    std::istringstream linestream(line);
    std::istream_iterator<string> begin(linestream), end;
    vector<string> linecontent(begin, end);
    utime = stol(linecontent[14 - offset]);
    stime = stol(linecontent[15 - offset]);
    cutime = stol(linecontent[16 - offset]);
    cstime = stol(linecontent[17 - offset]);
    totalTime = utime + stime + cutime + cstime;
  }
  return totalTime;
}
// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() 
{
    vector<string> cpus = CpuUtilization();
  return stol(cpus[kUser_])
        + stol(cpus[kNice_])
        + stol(cpus[kSystem_])
        + stol(cpus[kIRQ_])
        + stol(cpus[kSoftIRQ_])
        + stol(cpus[kSteal_])
        + stol(cpus[kGuest_])
        + stol(cpus[kGuestNice_]);
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() 
{
  vector<string> cpus = CpuUtilization();
  return stol(cpus[kIdle_]) + stol(cpus[kIOwait_]);
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() 
{
    string line;
  string value;
  string cpu;
  vector<string> v_cpu;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> cpu;
    while(linestream >> value) {
      v_cpu.push_back(value);
    }
  }
  return v_cpu;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() 
{
  string line;
  string key;
  int value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          return value;
  }}}}
  return value;
}

#define FREQ sysconf(_SC_CLK_TCK)
float LinuxParser::Cpu(int pid) {
  float cpuUsage;
  long totalTime = ActiveJiffies(pid);
  long upTimeProcess = UpTime(pid);
  cpuUsage = ((float)totalTime / FREQ) / upTimeProcess;
  return cpuUsage;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() 
{
  string line;
  string key;
  int value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          return value;
  }}}}
  return value;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) //[[maybe_unused]]) { return string(); }
{
  string line;
  string key;
  string value;
  string pidstring = to_string(pid);
  std::ifstream filestream(kProcDirectory + pidstring + kCmdlineFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
  //     std::istringstream linestream(line);
  //     while (linestream >> key >> value) {
  //       if (key == "VmSize:") {
  //         return value;
  // }}}}
  return line;
}}}
// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) //[[maybe_unused]]) { return string(); }
{
  string line;
  string key;
  string value;
  string pidstring = to_string(pid);
  std::ifstream filestream(kProcDirectory + pidstring + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          return value;
  }}}}
  return value;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) //[[maybe_unused]]) { return string(); }
{
  string line, key, value;
  string pidstring = to_string(pid);
  std::ifstream filestream(kProcDirectory + pidstring + kStatusFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);
      if (key == "Uid:") {
        return value;
  }}}
  return value;
}
// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) //[[maybe_unused]]) { return string(); }
{
  string line;
  string key;
  string value;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), '/', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "root:x:0:0:root:") {
          std::replace(value.begin(), value.end(), ':', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) //[[maybe_unused]]) { return 0; }
{
    string line;
  long startTimeInSeconds, startTimeInClocks, upTimeProcess;
  long upTimeSystem = UpTime();
  int const offset = 1;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    getline(filestream, line);
    std::istringstream linestream(line);
    std::istream_iterator<string> begin(linestream), end;
    vector<string> linecontent(begin, end);
    startTimeInClocks = stol(linecontent[22 - offset]);
    startTimeInSeconds =  startTimeInClocks / FREQ;
    upTimeProcess = upTimeSystem - startTimeInSeconds;
  }
  return upTimeProcess;
  // long _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, uptime;
  // string line;
  // string pidstring = to_string(pid);
  // std::ifstream stream(kProcDirectory + pidstring + kStatFilename);
  // if (stream.is_open()) {
  //   std::getline(stream, line);
  //   std::istringstream linestream(line);
  //   linestream >> _1>>_2>>_3>>_4>>_5>>_6>>_7>>_8>>_9>>_10>>_11>>_12>>_13>>_14>>_15>>_16>>_17>>_18>>_19>>_20 >> uptime;
  // }
  // return uptime;
}
