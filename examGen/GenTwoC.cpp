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
   : GenItem{}
   , pText_{}
   , pO1_{}
   , pO2_{}
   , pO3_{}
   , pO4_{}
   , N_{0}
   , binaryN_{}
{
   type_ = "GenTwoC";
   LOGD(id_ + ", initialised");
}

void GenTwoC::prepare()
{
   N_ = -randomProfile_s.generate(s_R0);

   stringstream sN;
   sN << N_;

   pText_ = std::shared_ptr<GenText>(
      new GenText("Wat is de binaire notatie van " + sN.str() +
                  " (volgens de two�s complement notatie in 8 bits)?"));
   pO1_ = std::shared_ptr<GenOption>(new GenOption(util::Binary(N_, 8)));
   pO2_ = std::shared_ptr<GenOption>(new GenOption(util::Binary(N_ - 1, 8)));
   pO3_ = std::shared_ptr<GenOption>(new GenOption(util::Binary(N_ + 1, 8)));
   pO4_ =
      std::shared_ptr<GenOption>(new GenOption(util::Binary(128 + abs(N_), 8)));

   generators_[0]->add(pText_);
   addToOptions(pO1_, true);
   addToOptions(pO2_);
   addToOptions(pO3_);
   addToOptions(pO4_);
   // randomizeOptions();
}
