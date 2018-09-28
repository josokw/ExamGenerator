#include "Util.h"

#include <boost/lexical_cast.hpp>
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

      subResult = boost::lexical_cast<std::string>(b1) + " & " +
                  boost::lexical_cast<std::string>(b2) + " & " +
                  boost::lexical_cast<std::string>(b3) + " & " +
                  boost::lexical_cast<std::string>(boolExpr(b1, b2, b3)) + " ";
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
      subResult = boost::lexical_cast<std::string>(b1) + " " +
                  boost::lexical_cast<std::string>(b2) + "  " +
                  boost::lexical_cast<std::string>(boolExpr(b1, b2)) + "\n";
      result.push_back(subResult);
   }

   return result;
}
