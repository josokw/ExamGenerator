#ifndef LOG_H
#define LOG_H

#include "Logger.h"

#include <string>

#define STRINGIZE(x) STRINGIZE_(x)
#define STRINGIZE_(x) #x

#define LOG(msg) log(std::string(__func__) + "() " + msg)
#define LOGE(msg) log("E    " + std::string(__func__) + "() " + msg)
#define LOGW(msg) log(" W   " + std::string(__func__) + "() " + msg)
#define LOGI(msg) log("  I  " + std::string(__func__) + "() " + msg)
#define LOGD(msg, level)                                                       \
   logDebug("   D " + std::string(__func__) + "() " + msg, level)

#define LOGCI(condition, msg)                                                  \
   log(condition, "  I  " + std::string(__func__) +                            \
                     "() condition: " + STRINGIZE(condition) + " " + msg)
#define LOGCW(condition, msg)                                                  \
   log(condition, " W   " + std::string(__func__) +                            \
                     "() condition: " + STRINGIZE(condition) + " " + msg)
#define LOGCE(condition, msg)                                                  \
   log(condition, "E    " + std::string(__func__) +                            \
                     "() condition: " + STRINGIZE(condition) + " " + msg)

void log(const std::string &msg);
void log(const char *msg);
void logDebug(const std::string &msg, int level);
void logDebug(const char *msg, int level);
void log(bool condition, const std::string &msg);
void log(bool condition, const char *msg);

#endif // LOG_H
