#include "ClocksTimers.h"
#include <ctime>

std::string timepointAsString(const std::chrono::system_clock::time_point &tp)
{
   // Convert to system time (C-lib and POSIX)
   time_t t{std::chrono::system_clock::to_time_t(tp)};
   // Convert to calendar time
   std::string ts{ctime(&t)}; 
   // Skip trailing newline=
   ts.resize(ts.size() - 1);
     
   return ts;
}
