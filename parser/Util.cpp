#include "Util.h"

#include <algorithm>
#include <string>
#include <vector>

std::string util::Binary(int n, int maxBits)
{
   std::string result;
   int nBits = 8 * sizeof(n);

   if (nBits > maxBits) {
      nBits = maxBits;
   }

   for (int i = nBits - 1; i >= 0; i--) {
      int bit = ((n >> i) & 1);
      result += (bit ? "1" : "0");
   }

   return result;
}

std::vector<std::string> util::toTruthTable(util::bool3Pars_t boolExpr)
{
   std::vector<std::string> result;
   std::string subResult;

   for (unsigned char i = 0; i < 8; ++i) {
      bool b3 = ((i >> 0) & 1) == 1;
      bool b2 = ((i >> 1) & 1) == 1;
      bool b1 = ((i >> 2) & 1) == 1;

      subResult = std::to_string(b1) + " & " + std::to_string(b2) + " & " +
                  std::to_string(b3) + " & " +
                  std::to_string(boolExpr(b1, b2, b3)) + " ";
      result.push_back(subResult);
   }

   return result;
}

std::vector<std::string> util::toTruthTable(util::bool2Pars_t boolExpr)
{
   std::vector<std::string> result;
   std::string subResult;

   for (unsigned int i = 0; i < 4; ++i) {
      bool b2 = (i >> 1) == 1;
      bool b1 = (i >> 2) == 1;
      subResult = std::to_string(b1) + " " + std::to_string(b2) + "  " +
                  std::to_string(boolExpr(b1, b2)) + "\n";
      result.push_back(subResult);
   }

   return result;
}

std::string util::removeNewLines(const std::string &str)
{
   std::string result;

   std::transform(begin(str), end(str), std::back_inserter(result),
                  [](char c) { return (c == '\n' ? ' ' : c); });

   return result;
}

std::string util::limitSize(const std::string &str, size_t maxSize)
{
   return (str.size() < maxSize) ? str : str.substr(0, maxSize);
}
