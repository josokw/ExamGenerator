#include "GenNestedFor.h"
#include "GenCodeText.h"
#include "GenOption.h"
#include "GenStem.h"
#include "GenText.h"
#include "Util.h"

#include <sstream>

using namespace std;

std::tuple<Random::Random::range_t, int, std::list<int>, int>
   GenNestedFor::s_R0(Random::range_t(1, 2), 0, std::list<int>(), 1);
std::tuple<Random::Random::range_t, int, std::list<int>, int>
   GenNestedFor::s_R1(Random::range_t(0, 1), 0, std::list<int>(), 0);
std::tuple<Random::Random::range_t, int, std::list<int>, int>
   GenNestedFor::s_R2(Random::range_t(2, 3), 0, std::list<int>(), 1);

GenNestedFor::GenNestedFor()
   : pText_{new GenText("What is the value of the variable $result$ after "
                        "executing the following code block:")}
   , pCodeText_{}
   , pO1_{}
   , pO2_{}
   , pO3_{}
   , pO4_{}
{
   type_ = "GenNestedFor";
   addToStem(pText_);

   int initResultaat = randomProfile_s.generate(s_R0);
   int iStart = randomProfile_s.generate(s_R1);
   int jStart = randomProfile_s.generate(s_R2);
   int iMax = iStart + 2;
   int jMax = jStart + 2;

   string sinitResultaat(std::to_string(initResultaat));
   string siStart(std::to_string(iStart));
   string sjStart(std::to_string(jStart));

   string siMax{std::to_string(iMax)};
   string sjMax{std::to_string(jMax)};

   pCodeText_ = std::shared_ptr<GenCodeText>(
      new GenCodeText("c",
                      "int i = 0;\n"
                      "int j = 0;\n"
                      "int result = " +
                         sinitResultaat +
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
                         "}\n"));

   int Resultaat = correctAnswer(initResultaat, iStart, jStart, iMax, jMax);
   string sResultaat = std::to_string(Resultaat);

   pO1_ = std::shared_ptr<GenOption>(new GenOption("4"));
   pO2_ = std::shared_ptr<GenOption>(new GenOption("8"));
   pO3_ = std::shared_ptr<GenOption>(new GenOption("16"));
   pO4_ = std::shared_ptr<GenOption>(new GenOption("32"));

   addToStem(pCodeText_);
   addToOptions(pO1_, "4" == sResultaat);
   addToOptions(pO2_, "8" == sResultaat);
   addToOptions(pO3_, "16" == sResultaat);
   addToOptions(pO4_, "32" == sResultaat);
}

void GenNestedFor::prepare() {}

int GenNestedFor::correctAnswer(int InitValue, int iStart, int jStart, int iMax,
                                int jMax)
{
   int resultaat = InitValue;

   for (int i = iStart; i < iMax; i++) {
      for (int j = jStart; j < jMax; j++) {
         resultaat = resultaat * 2;
      }
   }

   return resultaat;
}
