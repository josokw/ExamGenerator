#include "GenTwoC.h"
#include "GenCodeText.h"
#include "GenOption.h"
#include "GenStem.h"
#include "GenText.h"
#include "Util.h"

// #include "boost/tuple/tuple.hpp"
// #include "boost/tuple/tuple_comparison.hpp"
// #include "boost/tuple/tuple_io.hpp"

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
{
   type_ = "TwoC";
}

GenTwoC::~GenTwoC()
{
   // IGenerator::write(clog) << " ##### DTOR" << endl;
}

void GenTwoC::prepare()
{
   N = -randomProfile_s.generate(s_R0);

   stringstream sN;
   sN << N;

   m_pText = std::shared_ptr<GenText>(
      new GenText("Wat is de binaire notatie van " + sN.str() +
                  " (volgens de two�s complement notatie in 8 bits)?"));
   m_pO1 = std::shared_ptr<GenOption>(new GenOption(util::Binary(N, 8)));
   m_pO2 = std::shared_ptr<GenOption>(new GenOption(util::Binary(N - 1, 8)));
   m_pO3 = std::shared_ptr<GenOption>(new GenOption(util::Binary(N + 1, 8)));
   m_pO4 =
      std::shared_ptr<GenOption>(new GenOption(util::Binary(128 + abs(N), 8)));

   generators_[0]->add(m_pText);
   addToOptions(m_pO1, true);
   addToOptions(m_pO2);
   addToOptions(m_pO3);
   addToOptions(m_pO4);
   // randomizeOptions();
}
