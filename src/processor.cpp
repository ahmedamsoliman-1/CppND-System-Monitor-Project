#include "processor.h"
#include "linux_parser.h"
#include <thread>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() 
{
    long const prev_idle = LinuxParser::IdleJiffies();
    long const prev_nonidle = LinuxParser::ActiveJiffies();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    long idle = LinuxParser::IdleJiffies();
    long nonidle = LinuxParser::ActiveJiffies();
    idle = idle - prev_idle;
    nonidle = nonidle - prev_nonidle;
    return (float) nonidle / (nonidle + idle);
}