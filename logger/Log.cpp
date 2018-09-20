#include "Log.h"
#include "Logger.h"

namespace
{
  Logger& logger =  Logger::instance();
}

void log(const std::string& msg)
{
  logger.log(msg);
}

void logDebug(const char* msg)
{
  logger.logDebug(msg);
}

void logDebug(const std::string& msg)
{
  logger.logDebug(msg);
}

void log(const char* msg)
{
  logger.log(msg);
}

void log(bool condition, const std::string& msg)
{
  if (condition) log(msg);
}

void log(bool condition, const char* msg)
{
  if (condition) log(msg);
}

