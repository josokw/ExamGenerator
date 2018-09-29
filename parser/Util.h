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

} // namespace util

#endif
