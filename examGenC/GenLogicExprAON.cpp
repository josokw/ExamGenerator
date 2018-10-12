#include "GenLogicExprAON.h"
#include "GenCodeText.h"
#include "GenOption.h"
#include "GenOptions.h"
#include "GenStem.h"
#include "GenText.h"
#include "LaTeX.h"
#include "Log.h"

#include <sstream>
#include <tuple>

using namespace std;

std::tuple<Random::range_t, int, std::list<int>, int>
   GenLogicExprAON::R0_s(Random::range_t(0, 3), 0, std::list<int>(), 3);

GenLogicExprAON::GenLogicExprAON()
   : GenItem{}
   , pText_{new GenText(
        "\\needspace{6cm} The variables $x$, $y$, $z$ and $result$ are all "
        "int typed. True equals 1 and false equals 0. What is the truth table "
        "for the next logical expression?")}
   , codeText_{nullptr}
   , pO1_{}
   , pO2_{}
   , pO3_{}
   , pO4_{}
   , AON_{0}
   , andF_(std::bind(&GenLogicExprAON::and_, this, std::placeholders::_1,
                     std::placeholders::_2))
   , orF_(std::bind(&GenLogicExprAON::or_, this, std::placeholders::_1,
                    std::placeholders::_2))
   , notF_(std::bind(&GenLogicExprAON::not_, this, std::placeholders::_1))
   , equF_(std::bind(&GenLogicExprAON::equ_, this, std::placeholders::_1))
{
   type_ = "GenLogicExprAON";
   generators_[0]->add(pText_);
   setPreProOptions("\\begin{multicols}{4}{\n");
   setPostProOptions("\n}\n\\end{multicols}\n");

   AON_ = randomProfile_s.generate(R0_s);

   std::string logicExpr{};

   switch (AON_) {
      case 0:
         // ANOE
         logicExpr = "int result = (x && y) || (!z);";
         //    LD += latex::LogicBlock("AND", 20, 40, 20);
         //    LD += latex::LogicBlock("NOT", 20, 10, 20);
         //    LD += latex::LogicBlock("OR", 60, 40, 20);
         //    LD += latex::LogicEquate(100, 50, 20);
         break;
      case 1:
         // ONAE
         logicExpr = "int result = (x || y) && (!z);";
         //    LD += latex::LogicBlock("OR", 20, 40, 20);
         //    LD += latex::LogicBlock("NOT", 20, 10, 20);
         //    LD += latex::LogicBlock("AND", 60, 40, 20);
         //    LD += latex::LogicEquate(100, 50, 20);
         break;
      case 2:
         // AEON
         logicExpr = "int result = !((x && y) || z);";
         //    LD += latex::LogicBlock("AND", 20, 40, 20);
         //    LD += latex::LogicEquate(20, 20, 20);
         //    LD += latex::LogicBlock("OR", 60, 40, 20);
         //    LD += latex::LogicBlock("NOT", 100, 40, 20);
         break;
      case 3:
         // OEAN
         logicExpr = "int result = !((x || y) && z)";
         //    LD += latex::LogicBlock("OR", 20, 40, 20);
         //    LD += latex::LogicEquate(20, 20, 20);
         //    LD += latex::LogicBlock("AND", 60, 40, 20);
         //    LD += latex::LogicBlock("NOT", 100, 40, 20);
         break;
   }

   std::shared_ptr<GenCodeText> pLogicExpr(new GenCodeText("C", logicExpr));
   generators_[0]->add(pLogicExpr);

   util::bool3Pars_t logicF(
      std::bind(&GenLogicExprAON::logicD_, this, std::placeholders::_1,
                std::placeholders::_2, std::placeholders::_3));
   std::vector<std::string> truthTable = util::toTruthTable(logicF);
   string tt;

   // Correct option
   tt +=
      "\\scriptsize\n\\begin{tabular}{| c | c | c || c |}\n"
      "\\hline\n"
      "x & y & z & result\\\\\n"
      "\\hline\n";
   for (size_t i = 0; i < truthTable.size(); ++i) {
      tt += truthTable[i] + " \\\\\n";
   }
   tt +=
      "\\hline\n"
      "\\end{tabular}\n"
      "\\normalsize\n";
   pO1_ = std::shared_ptr<GenOption>(new GenOption(tt));

   // New option, not correct
   tt.clear();
   ++AON_;
   AON_ %= 4;
   truthTable = util::toTruthTable(logicF);
   tt +=
      "\\scriptsize\n\\begin{tabular}{| c | c | c || c |}\n"
      "\\hline\n"
      "x & y & z & result\\\\\n"
      "\\hline\n";
   for (size_t i = 0; i < truthTable.size(); ++i) {
      tt += truthTable[i] + " \\\\\n";
   }
   tt +=
      "\\hline\n"
      "\\end{tabular}\n"
      "\\normalsize\n";
   pO2_ = std::shared_ptr<GenOption>(new GenOption(tt));

   // New option, not correct
   tt.clear();
   ++AON_;
   AON_ %= 4;
   truthTable = util::toTruthTable(logicF);
   tt +=
      "\\scriptsize\n\\begin{tabular}{| c | c | c || c |}\n"
      "\\hline\n"
      "x & y & z & result\\\\\n"
      "\\hline\n";

   for (size_t i = 0; i < truthTable.size(); ++i) {
      tt += truthTable[i] + " \\\\\n";
   }
   tt +=
      "\\hline\n"
      "\\end{tabular}\n"
      "\\normalsize\n";
   pO3_ = std::shared_ptr<GenOption>(new GenOption(tt));

   // New option, not correct
   tt.clear();
   ++AON_;
   AON_ %= 4;
   truthTable = util::toTruthTable(logicF);
   tt +=
      "\\scriptsize\n\\begin{tabular}{| c | c | c ||  c |}\n"
      "\\hline\n"
      "x & y & z & result\\\\\n"
      "\\hline\n";
   for (size_t i = 0; i < truthTable.size(); ++i) {
      tt += truthTable[i] + "\\\\\n";
   }
   tt +=
      "\\hline\n"
      "\\end{tabular}\n"
      "\\normalsize\n";
   pO4_ = std::shared_ptr<GenOption>(new GenOption(tt));

   addToOptions(pO1_, true);
   addToOptions(pO2_);
   addToOptions(pO3_);
   addToOptions(pO4_);
   shuffleON();
   LOGD(id_ + ", initialised");
}

void GenLogicExprAON::prepare() {}

bool GenLogicExprAON::logicD_(bool b1, bool b2, bool b3)
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
         break;
   }

   return lf4(lf3(lf1(b1, b2), lf2(b3)));
}
