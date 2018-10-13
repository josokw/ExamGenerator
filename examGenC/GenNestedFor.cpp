#include "GenNestedFor.h"
#include "GenCodeText.h"
#include "GenOption.h"
#include "GenStem.h"
#include "GenText.h"
#include "Util.h"

#include <sstream>

std::tuple<Random::Random::range_t, int, std::list<int>, int>
   GenNestedFor::s_R0(Random::range_t(1, 2), 0, std::list<int>(), 1);
std::tuple<Random::Random::range_t, int, std::list<int>, int>
   GenNestedFor::s_R1(Random::range_t(0, 1), 0, std::list<int>(), 0);
std::tuple<Random::Random::range_t, int, std::list<int>, int>
   GenNestedFor::s_R2(Random::range_t(2, 3), 0, std::list<int>(), 1);

GenNestedFor::GenNestedFor()
   : GenItem{}
{
   type_ = "GenNestedFor";

   auto pText = std::make_shared<GenText>(
      "What is the value of the variable $result$ after "
      "executing the following code:");
   addToStem(pText);

   int initResult = randomProfile_s.generate(s_R0);
   int iStart = randomProfile_s.generate(s_R1);
   int jStart = randomProfile_s.generate(s_R2);
   int iMax = iStart + 2;
   int jMax = jStart + 2;

   std::string sinitResult(std::to_string(initResult));
   std::string siStart(std::to_string(iStart));
   std::string sjStart(std::to_string(jStart));

   std::string siMax{std::to_string(iMax)};
   std::string sjMax{std::to_string(jMax)};

   auto pCodeText =
      std::make_shared<GenCodeText>("c",
                                    "int i = 0;\n"
                                    "int j = 0;\n"
                                    "int result = " +
                                       sinitResult +
                                       ";\n\n"
                                       "for (i = " +
                                       siStart + "; i < " + siMax +
                                       "; i++)\n"
                                       "{\n"
                                       "   for (j = " +
                                       sjStart + "; j < " + sjMax +
                                       "; j++)\n"
                                       "   {\n"
                                       "      result = result * 2;\n"
                                       "   }\n"
                                       "}\n");

   addToStem(pCodeText);

   int result = correctAnswer(initResult, iStart, jStart, iMax, jMax);
   std::string sResult = std::to_string(result);
   auto pO1 = std::make_shared<GenOption>("4");
   auto pO2 = std::make_shared<GenOption>("8");
   auto pO3 = std::make_shared<GenOption>("16");
   auto pO4 = std::make_shared<GenOption>("32");

   addToOptions(pO1, "4" == sResult);
   addToOptions(pO2, "8" == sResult);
   addToOptions(pO3, "16" == sResult);
   addToOptions(pO4, "32" == sResult);
}

void GenNestedFor::prepare() {}

int GenNestedFor::correctAnswer(int initValue, int iStart, int jStart, int iMax,
                                int jMax)
{
   int result = initValue;

   for (int i = iStart; i < iMax; i++) {
      for (int j = jStart; j < jMax; j++) {
         result = result * 2;
      }
   }

   return result;
}
