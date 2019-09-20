#include "Log.h"
#include "Logger.h"

void log(const std::string &msg)
{
   Logger::instance().log(msg);
}

void logDebug(const char *msg, int level)
{
   Logger::instance().logDebug(msg, level);
}

void logDebug(const std::string &msg, int level)
{
   Logger::instance().logDebug(msg, level);
}

void log(const char *msg)
{
   Logger::instance().log(msg);
}

void log(bool condition, const std::string &msg)
{
   if (condition) {
      log(msg);
   }
}

void log(bool condition, const char *msg)
{
   if (condition) {
      log(msg);
   }
}
