#include "ncurses_display.h"
#include "system.h"

int main() 
{
  System system;
  NCursesDisplay::Display(system);
}

// Main instaniate system object and pass to Display function !