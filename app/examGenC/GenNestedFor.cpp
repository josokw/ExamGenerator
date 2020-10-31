#include "GenNestedFor.h"
#include "GenCodeText.h"
#include "GenOption.h"
#include "GenStem.h"
#include "GenText.h"
#include "Log.h"
#include "Util.h"

RandomProfile::fullR_t GenNestedFor::R0_s(RandomProfile::range_t(1, 2), 0,
                                          std::list<int>(), 1);
RandomProfile::fullR_t GenNestedFor::R1_s(RandomProfile::range_t(0, 1), 0,
                                          std::list<int>(), 0);
RandomProfile::fullR_t GenNestedFor::R2_s(RandomProfile::range_t(2, 3), 0,
                                          std::list<int>(), 1);

GenNestedFor::GenNestedFor()
   : GenNestedFor{"NOT-DEFINED"}
{
}

GenNestedFor::GenNestedFor(std::string_view id)
   : GenItem{id}
{
   type_ = __func__;

   LOGD("'" + id_ + "', initialised", 2);
}

void GenNestedFor::prepare()
{
   LOGD(type_ + ": '" + id_ + "'", 3);

   auto pText = std::make_shared<GenText>(
      id_ + ".txt",
      "What is the value of the variable $result$ after "
      "executing the following nested for loop:");
   addToStem(pText);

   int initResult = randomProfile_s.generate(R0_s);
   int iStart = randomProfile_s.generate(R1_s);
   int jStart = randomProfile_s.generate(R2_s);
   int iMax = iStart + 2;
   int jMax = jStart + 2;

   std::string sinitResult(std::to_string(initResult));
   std::string siStart(std::to_string(iStart));
   std::string sjStart(std::to_string(jStart));

   std::string siMax{std::to_string(iMax)};
   std::string sjMax{std::to_string(jMax)};

   auto pCodeText =
      // ANSI-C
      // std::make_shared<GenCodeText>(id_ + ".ctxt", "c",
      //                               "int i = 0;\n"
      //                               "int j = 0;\n"
      //                               "int result = " +
      //                                  sinitResult +
      //                                  ";\n\n"
      //                                  "for (i = " +
      //                                  siStart + "; i < " + siMax +
      //                                  "; i++)\n"
      //                                  "{\n"
      //                                  "   for (j = " +
      //                                  sjStart + "; j < " + sjMax +
      //                                  "; j++)\n"
      //                                  "   {\n"
      //                                  "      result = result * 2;\n"
      //                                  "   }\n"
      //                                  "}\n");
   std::make_shared<GenCodeText>(id_ + ".ctxt", "c",
                                 "int result = " +
                                    sinitResult +
                                    ";\n\n"
                                    "for (int i = " +
                                    siStart + "; i < " + siMax +
                                    "; i++)\n"
                                    "{\n"
                                    "   for (int j = " +
                                    sjStart + "; j < " + sjMax +
                                    "; j++)\n"
                                    "   {\n"
                                    "      result = result * 2;\n"
                                    "   }\n"
                                    "}\n");

   addToStem(pCodeText);

   int result = correctAnswer(initResult, iStart, jStart, iMax, jMax);
   auto pO1 = std::make_shared<GenOption>("O1", "4");
   auto pO2 = std::make_shared<GenOption>("O2", "8");
   auto pO3 = std::make_shared<GenOption>("O3", "16");
   auto pO4 = std::make_shared<GenOption>("O4", "32");

   addToOptions(pO1, 4 == result);
   addToOptions(pO2, 8 == result);
   addToOptions(pO3, 16 == result);
   addToOptions(pO4, 32 == result);
}

int GenNestedFor::correctAnswer(int initResult, int iStart, int jStart,
                                int iMax, int jMax)
{
   int result = initResult;

   for (int i = iStart; i < iMax; i++) {
      for (int j = jStart; j < jMax; j++) {
         result = result * 2;
      }
   }

   return result;
}
