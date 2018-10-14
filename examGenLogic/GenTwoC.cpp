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
   GenTwoC::R0_s(Random::range_t(5, 12), 0, std::list<int>(), 4);

GenTwoC::GenTwoC()
   : GenItem{}
{
   type_ = "GenTwoC";
   LOGD(id_ + ", initialised");
}

void GenTwoC::prepare()
{
   auto N = -randomProfile_s.generate(R0_s);

   auto pText = std::make_shared<GenText>("What is the binary notation for " +
                                          std::to_string(N) +
                                          " in 8 bits 2-complement notation?");
   auto pO1 = std::make_shared<GenOption>(util::Binary(N - 1, 8));
   auto pO2 = std::make_shared<GenOption>(util::Binary(N, 8));
   auto pO3 = std::make_shared<GenOption>(util::Binary(N + 1, 8));
   auto pO4 = std::make_shared<GenOption>(util::Binary(128 + abs(N), 8));

   generators_[0]->add(pText);
   addToOptions(pO1);
   addToOptions(pO2, true);
   addToOptions(pO3);
   addToOptions(pO4);
   shuffleON();
   GenItem::prepare();
}
