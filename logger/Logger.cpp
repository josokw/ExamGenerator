#include "Logger.h"
#include "ClocksTimers.h"
#include "ExamGeneratorConfig.h"
#include "Log.h"

#include <chrono>
#include <iostream>

Logger &Logger::instance()
{
   static Logger logger;
   return logger;
}

Logger::~Logger()
{
   LOGI("LOGGER closed");
   logFile_.close();
}

void Logger::setFilename(const std::string &filename)
{
   logFile_.close();
   logFile_.open(filename.c_str());
   if (logFile_) {
      logFilename_ = filename;
   }
   LOGI("LOGGER filename: " + logFilename_.c_str());
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
   , logFilename_{LOGFILENAME}
   , logFile_{logFilename_}
   , inDebugMode_{false}
{
   setDebugMode();
   if (!logFile_) {
      std::cerr << "\n\tERROR cannot create logfile\n";
   }
}
