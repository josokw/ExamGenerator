#ifndef UTIL_H
#define UTIL_H

#include <functional>
#include <sstream>
#include <string>
#include <vector>

namespace util {

std::string Binary(int n, int maxBits);

typedef std::function<bool(bool, bool, bool)> bool3Pars_t;
typedef std::function<bool(bool, bool)> bool2Pars_t;
typedef std::function<bool(bool)> bool1Pars_t;

std::vector<std::string> toTruthTable(bool3Pars_t boolExpr);
std::vector<std::string> toTruthTable(bool2Pars_t boolExpr);

std::string removeNewLines(std::string_view str);
std::string limitSize(const std::string &str, size_t maxSize,
                      const std::string &addText = " ...");
std::string limitSize(const char *begin, const char *end, size_t maxSize,
                      const std::string &addText = " ...");

} // namespace util

#endif
