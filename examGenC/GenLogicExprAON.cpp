#include "GenLogicExprAON.h"
#include "GenCodeText.h"
#include "GenOption.h"
#include "GenText.h"
#include "Log.h"

#include <array>
#include <tuple>

RandomProfile::fullR_t GenLogicExprAON::R0_s(Random::range_t(0, 3), 0,
                                             std::list<int>(), 3);

GenLogicExprAON::GenLogicExprAON()
   : GenItem{}
   , AON_{randomProfile_s.generate(R0_s)}
{
   type_ = "GenLogicExprAON";

   LOGD(id_ + ", initialised");
}

void GenLogicExprAON::prepare()
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

   switch (AON_) {
      case 0:
         // ANOE
         logicExpr = "int result = (x && y) || (!z);";
         break;
      case 1:
         // ONAE
         logicExpr = "int result = (x || y) && (!z);";
         break;
      case 2:
         // AEON
         logicExpr = "int result = !((x && y) || z);";
         break;
      case 3:
         // OEAN
         logicExpr = "int result = !((x || y) && z)";
         break;
   }

   auto pCodeLogicExpr =
      std::make_shared<GenCodeText>("logicexpr", "C", logicExpr);
   addToStem(pCodeLogicExpr);

   std::vector<std::string> truthTable;

   const std::string starttt{
      "\\scriptsize\n\\begin{tabular}{| c | c | c || c |}\n"
      "\\hline\n"
      "x & y & z & result\\\\\n"
      "\\hline\n"};

   const std::string endtt{
      "\\hline\n"
      "\\end{tabular}\n"
      "\\normalsize\n"};

   std::array<std::shared_ptr<GenOption>, 4> options;
   bool first{true};
   std::string tt;

   util::bool3Pars_t logicF(
      std::bind(&GenLogicExprAON::logicExpr, this, std::placeholders::_1,
                std::placeholders::_2, std::placeholders::_3));

   for (auto &opt : options) {
      tt = starttt;
      truthTable = util::toTruthTable(logicF);
      for (auto &truth : truthTable) {
         tt += truth + " \\\\\n";
      }
      tt += endtt;
      opt = std::make_shared<GenOption>(tt);
      addToOptions(opt, first);
      first = false;
      ++AON_;
      AON_ %= 4;
   }
}

bool GenLogicExprAON::logicExpr(bool bl1, bool bl2, bool bl3)
{
   util::bool2Pars_t lf1;
   util::bool1Pars_t lf2;
   util::bool2Pars_t lf3;
   util::bool1Pars_t lf4;

   auto andF = [](bool b1, bool b2) { return b1 && b2; };
   auto orF = [](bool b1, bool b2) { return b1 || b2; };
   auto notF = [](bool b1) { return !b1; };
   auto equF = [](bool b1) { return b1; };

   switch (AON_) {
      case 0:
         // ANOE
         lf1 = andF;
         lf2 = notF;
         lf3 = orF;
         lf4 = equF;
         break;
      case 1:
         // ONAE
         lf1 = orF;
         lf2 = notF;
         lf3 = andF;
         lf4 = equF;
         break;
      case 2:
         // AEON
         lf1 = andF;
         lf2 = equF;
         lf3 = orF;
         lf4 = notF;
         break;
      case 3:
         // OEAN
         lf1 = orF;
         lf2 = equF;
         lf3 = andF;
         lf4 = notF;
         break;
      default:
         LOGE(type_ + ": " + id_ + ", AON_ = " + std::to_string(AON_) +
              " is unknown");
         break;
   }

   return lf4(lf3(lf1(bl1, bl2), lf2(bl3)));
}
