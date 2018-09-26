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
   : m_pText(new GenText("Wat is de waarde van Resultaat na uitvoering van het "
                         "volgende programmafragment?"))
   , m_pCodeText{}
   , m_pO1()
   , m_pO2()
   , m_pO3()
   , m_pO4()
{
   type_ = "NestedFor";
   addToStem(m_pText);

   int InitResultaat = randomProfile_s.generate(s_R0);
   int iStart = randomProfile_s.generate(s_R1);
   int jStart = randomProfile_s.generate(s_R2);
   int iMax = iStart + 2;
   int jMax = jStart + 2;

   string sInitResultaat(std::to_string(InitResultaat));
   string siStart(std::to_string(iStart));
   string sjStart(std::to_string(jStart));

   string siMax{std::to_string(iMax)};
   string sjMax{std::to_string(jMax)};

   m_pCodeText = std::shared_ptr<GenCodeText>(
      new GenCodeText("java", "int Resultaat = " + sInitResultaat +
                                 ";\n\n"
                                 "for (int i = " +
                                 siStart + "; i < " + siMax +
                                 "; i++)\n"
                                 "{\n"
                                 "   for (int j = " +
                                 sjStart + "; j < " + sjMax +
                                 "; j++)\n"
                                 "   {\n"
                                 "      Resultaat = Resultaat * 2;\n"
                                 "   }\n"
                                 "}\n"));

   int Resultaat = correctAnswer(InitResultaat, iStart, jStart, iMax, jMax);
   string sResultaat = std::to_string(Resultaat);

   m_pO1 = std::shared_ptr<GenOption>(new GenOption("4"));
   m_pO2 = std::shared_ptr<GenOption>(new GenOption("8"));
   m_pO3 = std::shared_ptr<GenOption>(new GenOption("16"));
   m_pO4 = std::shared_ptr<GenOption>(new GenOption("32"));

   addToStem(m_pCodeText);
   addToOptions(m_pO1, "4" == sResultaat);
   addToOptions(m_pO2, "8" == sResultaat);
   addToOptions(m_pO3, "16" == sResultaat);
   addToOptions(m_pO4, "32" == sResultaat);
}

GenNestedFor::~GenNestedFor()
{
   // IGenerator::write(clog) << " ##### DTOR" << endl;
}

void GenNestedFor::prepare() {}

int GenNestedFor::correctAnswer(int InitValue, int iStart, int jStart, int iMax,
                                int jMax)
{
   int Resultaat = InitValue;

   for (int i = iStart; i < iMax; i++) {
      for (int j = jStart; j < jMax; j++) {
         Resultaat = Resultaat * 2;
      }
   }

   return Resultaat;
}
