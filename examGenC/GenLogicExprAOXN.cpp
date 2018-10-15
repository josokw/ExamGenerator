#include "GenLogicExprAOXN.h"
#include "GenCodeText.h"
#include "GenOption.h"
#include "GenOptions.h"
#include "GenStem.h"
#include "GenText.h"
#include "LaTeX.h"
#include "Log.h"

#include <tuple>

std::tuple<Random::range_t, int, std::list<int>, int>
   GenLogicExprAOXN::R0_s(Random::range_t(0, 3), 0, std::list<int>(), 3);

GenLogicExprAOXN::GenLogicExprAOXN()
   : GenItem{}
   , AOXN_{randomProfile_s.generate(R0_s)}
   , andF(std::bind(&GenLogicExprAOXN::and_, this, std::placeholders::_1,
                    std::placeholders::_2))
   , orF(std::bind(&GenLogicExprAOXN::or_, this, std::placeholders::_1,
                   std::placeholders::_2))
   , xorF(std::bind(&GenLogicExprAOXN::xor_, this, std::placeholders::_1,
                    std::placeholders::_2))
   , notF(std::bind(&GenLogicExprAOXN::not_, this, std::placeholders::_1))
   , equF(std::bind(&GenLogicExprAOXN::equ, this, std::placeholders::_1))
{
   type_ = "GenLogicExprAOXN";

   LOGD(id_);
}

void GenLogicExprAOXN::prepare()
{
   LOGD(type_ + ": " + id_);

   auto pText = std::make_shared<GenText>(
      "\\needspace{8cm} The variables $x$, $y$, $z$ and $result$ are all "
      "int typed. True equals 1 and false equals 0. What is the truth table "
      "for the next logical expression?");
   addToStem(pText);

   setPreProOptions("\\begin{multicols}{4}{\n");
   setPostProOptions("\n}\n\\end{multicols}\n");

   std::string logicExpr;

   switch (AOXN_) {
      case 0:
         // ANXE
         logicExpr = "int result = (x && y) ^ (!z);";
         break;
      case 1:
         // XNAE
         logicExpr = "int result = (x ^ y) && (!z);";
         break;
      case 2:
         // AEXN
         logicExpr = "int result =!((x && y) ^ z);";
         break;
      case 3:
         // XEAN
         logicExpr = "int result = !((x ^ y) && z);";
         break;
   }

   auto pCodeLogicExpr = std::make_shared<GenCodeText>("C", logicExpr);
   addToStem(pCodeLogicExpr);

   util::bool3Pars_t logicF(
      std::bind(&GenLogicExprAOXN::logicExpr, this, std::placeholders::_1,
                std::placeholders::_2, std::placeholders::_3));
   std::vector<std::string> truthTable = util::toTruthTable(logicF);

   std::string tt;
   const std::string starttt{
      "\\scriptsize\n\\begin{tabular}{| c | c | c || c |}\n"
      "\\hline\n"
      "x & y & z & result\\\\\n"
      "\\hline\n"};
   const std::string endtt{
      "\\hline\n"
      "\\end{tabular}\n"
      "\\normalsize\n"};

   // Correct option
   tt += starttt;
   for (size_t i = 0; i < truthTable.size(); ++i) {
      tt += truthTable[i] + " \\\\\n";
   }
   tt += endtt;
   auto pO1 = std::make_shared<GenOption>(tt);

   // New option, not correct
   tt.clear();
   ++AOXN_;
   AOXN_ %= 4;
   truthTable = util::toTruthTable(logicF);
   tt += starttt;
   for (size_t i = 0; i < truthTable.size(); ++i) {
      tt += truthTable[i] + " \\\\\n";
   }
   tt += endtt;
   auto pO2 = std::make_shared<GenOption>(tt);

   // New option not correct
   tt.clear();
   ++AOXN_;
   AOXN_ %= 4;
   truthTable = util::toTruthTable(logicF);
   tt += starttt;
   for (size_t i = 0; i < truthTable.size(); ++i) {
      tt += truthTable[i] + " \\\\\n";
   }
   tt += endtt;
   auto pO3 = std::make_shared<GenOption>(tt);

   // New option, not correct
   tt.clear();
   ++AOXN_;
   AOXN_ %= 4;
   truthTable = util::toTruthTable(logicF);
   tt += starttt;
   for (size_t i = 0; i < truthTable.size(); ++i) {
      tt += truthTable[i] + "\\\\\n";
   }
   tt += endtt;
   auto pO4 = std::make_shared<GenOption>(tt);

   addToOptions(pO1, true);
   addToOptions(pO2);
   addToOptions(pO3);
   addToOptions(pO4);
}

bool GenLogicExprAOXN::logicExpr(bool b1, bool b2, bool b3)
{
   util::bool2Pars_t lf1;
   util::bool1Pars_t lf2;
   util::bool2Pars_t lf3;
   util::bool1Pars_t lf4;

   switch (AOXN_) {
      case 0:
         // ANXE
         lf1 = andF;
         lf2 = notF;
         lf3 = xorF;
         lf4 = equF;
         break;
      case 1:
         // XNAE
         lf1 = xorF;
         lf2 = notF;
         lf3 = andF;
         lf4 = equF;
         break;
      case 2:
         // AEXN
         lf1 = andF;
         lf2 = equF;
         lf3 = xorF;
         lf4 = notF;
         break;
      case 3:
         // XEAN
         lf1 = xorF;
         lf2 = equF;
         lf3 = andF;
         lf4 = notF;
         break;
      default:
         break;
   }

   return lf4(lf3(lf1(b1, b2), lf2(b3)));
}
