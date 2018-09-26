#include "GenTwoC.h"
#include "GenCodeText.h"
#include "GenOption.h"
#include "GenStem.h"
#include "GenText.h"
#include "Log.h"
#include "Util.h"

#include <list>
#include <sstream>
#include <vector>

using namespace std;

std::tuple<Random::range_t, int, std::list<int>, int>
   GenTwoC::s_R0(Random::range_t(5, 12), 0, std::list<int>(), 4);

GenTwoC::GenTwoC()
   : GenItem()
   , m_pText()
   , m_pO1()
   , m_pO2()
   , m_pO3()
   , m_pO4()
   , N_{0}
   , binaryN_{}
{
   type_ = "GenTwoC";
   LOGD(id_ + ", initialised");
}

GenTwoC::~GenTwoC()
{
   LOGD(id_);
}

void GenTwoC::prepare()
{
   N_ = -randomProfile_s.generate(s_R0);

   stringstream sN;
   sN << N_;

   m_pText = std::shared_ptr<GenText>(
      new GenText("Wat is de binaire notatie van " + sN.str() +
                  " (volgens de two�s complement notatie in 8 bits)?"));
   m_pO1 = std::shared_ptr<GenOption>(new GenOption(util::Binary(N_, 8)));
   m_pO2 = std::shared_ptr<GenOption>(new GenOption(util::Binary(N_ - 1, 8)));
   m_pO3 = std::shared_ptr<GenOption>(new GenOption(util::Binary(N_ + 1, 8)));
   m_pO4 =
      std::shared_ptr<GenOption>(new GenOption(util::Binary(128 + abs(N_), 8)));

   generators_[0]->add(m_pText);
   addToOptions(m_pO1, true);
   addToOptions(m_pO2);
   addToOptions(m_pO3);
   addToOptions(m_pO4);
   // randomizeOptions();
}
