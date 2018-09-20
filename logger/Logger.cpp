#include "Logger.h"
#include "AppInfo.h"
#include "ClocksTimers.h"
#include "Log.h"

#include <chrono>

Logger &Logger::instance()
{
   static Logger logger;
   return logger;
}

Logger::~Logger()
{
   SET_FNAME("Logger::~Logger()");
   LOGI("LOGGER closed");
   logFile_.close();
}

void Logger::setFilename(const std::string &filename)
{
   // SET_FNAME("Logger::setFilename()");
   logFile_.close();
   logFile_.open(filename.c_str());
   if (logFile_) {
      logFilename_ = filename;
   }
   // LOGI("LOGGER filename: " + m_filename.c_str());
}

void Logger::log(const std::string &message)
{
   std::lock_guard<std::mutex> lock(logMutex_);
   logFile_ << timepointAsString(std::chrono::system_clock::now()) << "  "
            << message << std::endl;
}

void Logger::log(const char *message)
{
   std::lock_guard<std::mutex> lock(logMutex_);
   logFile_ << timepointAsString(std::chrono::system_clock::now()) << "  "
            << message << std::endl;
}

Logger::Logger()
   : logMutex_{}
   , logFilename_{APPNAME ".log"}
   , logFile_{}
   , inDebugMode_{false}
{
}
