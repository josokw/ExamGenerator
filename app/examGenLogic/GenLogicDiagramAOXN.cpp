#include "GenLogicDiagramAOXN.h"
#include "GenCodeText.h"
#include "GenOption.h"
#include "GenOptions.h"
#include "GenStem.h"
#include "GenText.h"
#include "LaTeX.h"
#include "Log.h"

#include <tuple>

RandomProfile::fullR_t GenLogicDiagramAOXN::R0_s(RandomProfile::range_t(0, 3),
                                                 0, std::list<int>(), 3);

GenLogicDiagramAOXN::GenLogicDiagramAOXN()
   : GenItem()
   , m_pText(new GenText(id_ + ".txt",
                         "\\needspace{17cm} What is the truth table "
                         "for the next diagram?"))
   , m_pO1()
   , m_pO2()
   , m_pO3()
   , m_pO4()
   , m_AON(0)
   , andF([=](bool b1, bool b2) { return and_(b1, b2); })
   , orF([=](bool b1, bool b2) { return or_(b1, b2); })
   , xorF([=](bool b1, bool b2) { return xor_(b1, b2); })
   , notF([=](bool b1) { return not_(b1); })
   , equF([=](bool b1) { return equ(b1); })
{
   type_ = __func__;
   generators_[0]->add(m_pText);
   setPreProOptions("\\begin{multicols}{4}{\n");
   setPostProOptions("\n}\n\\end{multicols}\n");

   m_AON = randomProfile_s.generate(R0_s);

   std::string LD(
      "\n\\\\\n"
      "\\ifx\\JPicScale\\undefined\\def\\JPicScale{1}\\fi\n"
      "\\def\\JPicScale{0.55}\n"
      "\\unitlength \\JPicScale mm\n"
      "\\begin{picture}(135,65)(0,0)\n"
      "\\linethickness{0.4mm}\n"

      "\\put(5,55){\\makebox(0,0)[cc]{X}}\n"
      "\\put(10,55){\\line(1,0){10}}\n"
      "\\put(5,45){\\makebox(0,0)[cc]{Y}}\n"
      "\\put(10,45){\\line(1,0){10}}\n"
      "\\put(5,20){\\makebox(0,0)[cc]{Z}}\n"
      "\\put(10,20){\\line(1,0){10}}\n"
      "\\put(135,50){\\makebox(0,0)[cc]{U}}\n");

   switch (m_AON) {
      case 0:
         // ANXE
         LD += latex::LogicBlock("AND", 20, 40, 20);
         LD += latex::LogicBlock("NOT", 20, 10, 20);
         LD += latex::LogicBlock("XOR", 60, 40, 20);
         LD += latex::LogicEquate(100, 50, 20);
         break;
      case 1:
         // XNAE
         LD += latex::LogicBlock("XOR", 20, 40, 20);
         LD += latex::LogicBlock("NOT", 20, 10, 20);
         LD += latex::LogicBlock("AND", 60, 40, 20);
         LD += latex::LogicEquate(100, 50, 20);
         break;
      case 2:
         // AEXN
         LD += latex::LogicBlock("AND", 20, 40, 20);
         LD += latex::LogicEquate(20, 20, 20);
         LD += latex::LogicBlock("XOR", 60, 40, 20);
         LD += latex::LogicBlock("NOT", 100, 40, 20);
         break;
      case 3:
         // XEAN
         LD += latex::LogicBlock("XOR", 20, 40, 20);
         LD += latex::LogicEquate(20, 20, 20);
         LD += latex::LogicBlock("AND", 60, 40, 20);
         LD += latex::LogicBlock("NOT", 100, 40, 20);
         break;
   }

   LD +=
      "\\put(40,50){\\line(1,0){10}}\n"
      "\\put(50,50){\\line(0,1){5}}\n"
      "\\put(50,55){\\line(1,0){10}}\n"
      "\\put(40,20){\\line(1,0){10}}\n"
      "\\put(50,20){\\line(0,1){25}}\n"
      "\\put(50,45){\\line(1,0){10}}\n"
      "\\put(50,45){\\line(1,0){10}}\n"
      "\\put(80,50){\\line(1,0){20}}\n"
      "\\put(120,50){\\line(1,0){10}}\n"
      "\\end{picture}\n";

   std::shared_ptr<GenText> pLogicD(new GenText(id_ + ".txt", LD));
   generators_[0]->add(pLogicD);

   util::bool3Pars_t logicF(
      [=](bool b1, bool b2, bool b3) { return logicD(b1, b2, b3); });
   std::vector<std::string> truthTable = util::toTruthTable(logicF);
   std::string tt;

   // Correct option
   tt +=
      "\\scriptsize\n\\begin{tabular}{| c | c | c || c |}\n"
      "\\hline\n"
      "X & Y & Z & U\\\\\n"
      "\\hline\n";
   for (size_t i = 0; i < truthTable.size(); ++i) {
      tt += truthTable[i] + " \\\\\n";
   }
   tt +=
      "\\hline\n"
      "\\end{tabular}\n"
      "\\normalsize\n";
   m_pO1 = std::shared_ptr<GenOption>(new GenOption(id_ + ".O2", tt));

   // New option, not correct
   tt.clear();
   ++m_AON;
   m_AON %= 4;
   truthTable = util::toTruthTable(logicF);
   tt +=
      "\\scriptsize\n\\begin{tabular}{| c | c | c || c |}\n"
      "\\hline\n"
      "X & Y & Z & U\\\\\n"
      "\\hline\n";
   for (size_t i = 0; i < truthTable.size(); ++i) {
      tt += truthTable[i] + " \\\\\n";
   }
   tt +=
      "\\hline\n"
      "\\end{tabular}\n"
      "\\normalsize\n";
   m_pO2 = std::shared_ptr<GenOption>(new GenOption(id_ + ".O2", tt));

   // New option, not correct
   tt.clear();
   ++m_AON;
   m_AON %= 4;
   truthTable = util::toTruthTable(logicF);
   tt +=
      "\\scriptsize\n\\begin{tabular}{| c | c | c || c |}\n"
      "\\hline\n"
      "X & Y & Z & U\\\\\n"
      "\\hline\n";
   for (size_t i = 0; i < truthTable.size(); ++i) {
      tt += truthTable[i] + " \\\\\n";
   }
   tt +=
      "\\hline\n"
      "\\end{tabular}\n"
      "\\normalsize\n";
   m_pO3 = std::shared_ptr<GenOption>(new GenOption(id_ + ".O3", tt));

   // New option, not correct
   tt.clear();
   ++m_AON;
   m_AON %= 4;
   truthTable = util::toTruthTable(logicF);
   tt +=
      "\\scriptsize\n\\begin{tabular}{| c | c | c ||  c |}\n"
      "\\hline\n"
      "X & Y & Z & U\\\\\n"
      "\\hline\n";
   for (size_t i = 0; i < truthTable.size(); ++i) {
      tt += truthTable[i] + "\\\\\n";
   }
   tt +=
      "\\hline\n"
      "\\end{tabular}\n"
      "\\normalsize\n";
   m_pO4 = std::shared_ptr<GenOption>(new GenOption(id_ + ".O4", tt));

   addToOptions(m_pO1, true);
   addToOptions(m_pO2);
   addToOptions(m_pO3);
   addToOptions(m_pO4);

   LOGD(id_ + ", initialised", 2);
}

void GenLogicDiagramAOXN::prepare()
{
   LOGD(type_ + "; " + id_, 3);
}

bool GenLogicDiagramAOXN::logicD(bool b1, bool b2, bool b3)
{
   util::bool2Pars_t lf1;
   util::bool1Pars_t lf2;
   util::bool2Pars_t lf3;
   util::bool1Pars_t lf4;

   switch (m_AON) {
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
