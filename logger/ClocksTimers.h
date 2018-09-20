#ifndef CLOCKSTIMERS_H
#define CLOCKSTIMERS_H

#include <chrono>
#include <string>

std::string timepointAsString(const std::chrono::system_clock::time_point &tp);

inline unsigned long timeSinceEpoch_msec()
{
   return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

inline unsigned long timeSinceEpoch_sec()
{
   return std::chrono::duration_cast<std::chrono::seconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

#endif
