#ifndef LOG_H
#define LOG_H

#include <string>

#define LOG(msg) log(std::string(__func__) + "() " + msg)
#define LOGE(msg) log("E    " + std::string(__func__) + "() " + msg)
#define LOGW(msg) log(" W   " + std::string(__func__) + "() " + msg)
#define LOGI(msg) log("  I  " + std::string(__func__) + "() " + msg)
#define LOGD(msg) logDebug("   D " + std::string(__func__) + "() " + msg)

#define LOGCI(condition, msg)                                                  \
   log(condition, "  I  " + std::string(__func__) + "() " + msg)
#define LOGCW(condition, msg)                                                  \
   log(condition, " W   " + std::string(__func__) + "() " + msg)
#define LOGCE(condition, msg)                                                  \
   log(condition, "E    " + std::string(__func__) + "() " + msg)

void log(const std::string &msg);
void log(const char *msg);
void logDebug(const std::string &msg);
void logDebug(const char *msg);
void log(bool condition, const std::string &msg);
void log(bool condition, const char *msg);

#endif // LOG_H
