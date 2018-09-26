#include "Util.h"

#include <boost/lexical_cast.hpp>
#include <string>
#include <vector>

std::string util::Binary(int n, int maxBits)
{
   std::string Result;
   int nBits = 8 * sizeof(n);

   if (nBits > maxBits) {
      nBits = maxBits;
   }

   for (int i = nBits - 1; i >= 0; i--) {
      int bit = ((n >> i) & 1);
      Result += (bit ? "1" : "0");
   }

   return Result;
}

std::vector<std::string> util::toTruthTable(util::bool3Pars_t boolExpr)
{
   std::vector<std::string> Result;
   std::string SubResult;
   bool b1(false);
   bool b2(false);
   bool b3(false);

   for (unsigned char i = 0; i < 8; ++i) {
      b3 = ((i >> 0) & 1) == 1;
      b2 = ((i >> 1) & 1) == 1;
      b1 = ((i >> 2) & 1) == 1;
      SubResult = boost::lexical_cast<std::string>(b1) + " & " +
                  boost::lexical_cast<std::string>(b2) + " & " +
                  boost::lexical_cast<std::string>(b3) + " & " +
                  boost::lexical_cast<std::string>(boolExpr(b1, b2, b3)) + " ";
      Result.push_back(SubResult);
   }

   return Result;
}

std::vector<std::string> util::toTruthTable(util::bool2Pars_t boolExpr)
{
   std::vector<std::string> Result;
   std::string SubResult;
   bool b1(false);
   bool b2(false);

   for (unsigned int i = 0; i < 4; ++i) {
      b2 = (i >> 1) == 1;
      b1 = (i >> 2) == 1;
      SubResult = boost::lexical_cast<std::string>(b1) + " " +
                  boost::lexical_cast<std::string>(b2) + "  " +
                  boost::lexical_cast<std::string>(boolExpr(b1, b2)) + "\n";
      Result.push_back(SubResult);
   }

   return Result;
}
