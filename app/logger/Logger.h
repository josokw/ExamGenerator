#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <mutex>
#include <string>

/// Class Logger is responsible for logging messages to a log file.
/// Implemented according to the singleton pattern.
/// Writing to the log file is protected by a mutex.
class Logger
{
public:
   static Logger &instance();

   Logger(const Logger &other) = delete;
   Logger &operator=(const Logger &logger) = delete;
   virtual ~Logger();

   void setFilename(const std::string &filename);
   void setDebugMode(bool on = true);
   void setLevel(int level) { level_ = level; }
   void log(const std::string &message);
   void log(const char *message);
   void logDebug(const std::string &message, int level)
   {
      if (level >= level_) {
         if (inDebugMode_) {
            log(message);
         }
      }
   }
   void logDebug(const char *message, int level)
   {
      if (level >= level_) {
         if (inDebugMode_) {
            log(message);
         }
      }
   }

protected:
   Logger();

private:
   std::mutex logMutex_;
   std::string logFilename_;
   std::ofstream logFile_;
   bool inDebugMode_;
   int level_;
};

#endif // LOGGER_H
