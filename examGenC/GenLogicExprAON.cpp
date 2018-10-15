#include "GenLogicExprAON.h"
#include "GenCodeText.h"
#include "GenOption.h"
#include "GenText.h"
#include "Log.h"

#include <array>
#include <tuple>

std::tuple<Random::range_t, int, std::list<int>, int>
   GenLogicExprAON::R0_s(Random::range_t(0, 3), 0, std::list<int>(), 3);

GenLogicExprAON::GenLogicExprAON()
   : GenItem{}
   , AON_{randomProfile_s.generate(R0_s)}
   , andF_(std::bind(&GenLogicExprAON::and_, this, std::placeholders::_1,
                     std::placeholders::_2))
   , orF_(std::bind(&GenLogicExprAON::or_, this, std::placeholders::_1,
                    std::placeholders::_2))
   , notF_(std::bind(&GenLogicExprAON::not_, this, std::placeholders::_1))
   , equF_(std::bind(&GenLogicExprAON::equ_, this, std::placeholders::_1))
{
   type_ = "GenLogicExprAON";

   LOGD(id_ + ", initialised");
}

void GenLogicExprAON::prepare()
{
   LOGD(type_ + ": " + id_);

   auto pText = std::make_shared<GenText>(
      "\\needspace{6cm} The variables $x$, $y$, $z$ and $result$ are all "
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

   auto pCodeLogicExpr = std::make_shared<GenCodeText>("C", logicExpr);
   addToStem(pCodeLogicExpr);

   util::bool3Pars_t logicF(
      std::bind(&GenLogicExprAON::logicExpr, this, std::placeholders::_1,
                std::placeholders::_2, std::placeholders::_3));
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

   for (auto &opt : options) {
      tt = starttt;
      truthTable = util::toTruthTable(logicF);
      for (size_t i = 0; i < truthTable.size(); ++i) {
         tt += truthTable[i] + " \\\\\n";
      }
      tt += endtt;
      opt = std::make_shared<GenOption>(tt);
      addToOptions(opt, first);
      first = false;
      ++AON_;
      AON_ %= 4;
   }
}

bool GenLogicExprAON::logicExpr(bool b1, bool b2, bool b3)
{
   util::bool2Pars_t lf1;
   util::bool1Pars_t lf2;
   util::bool2Pars_t lf3;
   util::bool1Pars_t lf4;

   switch (AON_) {
      case 0:
         // ANOE
         lf1 = andF_;
         lf2 = notF_;
         lf3 = orF_;
         lf4 = equF_;
         break;
      case 1:
         // ONAE
         lf1 = orF_;
         lf2 = notF_;
         lf3 = andF_;
         lf4 = equF_;
         break;
      case 2:
         // AEON
         lf1 = andF_;
         lf2 = equF_;
         lf3 = orF_;
         lf4 = notF_;
         break;
      case 3:
         // OEAN
         lf1 = orF_;
         lf2 = equF_;
         lf3 = andF_;
         lf4 = notF_;
         break;
      default:
         LOGE(type_ + ": " + id_ + ", AON_ = " + std::to_string(AON_) +
              " is unknown");
         break;
   }

   return lf4(lf3(lf1(b1, b2), lf2(b3)));
}
