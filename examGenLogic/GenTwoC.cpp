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

RandomProfile::fullR_t GenTwoC::R0_s(RandomProfile::range_t(5, 12), 0,
                                     std::list<int>(), 4);

GenTwoC::GenTwoC()
   : GenItem{}
{
   type_ = __func__;

   LOGD(id_ + ", initialised");
}

void GenTwoC::prepare()
{
   LOGD(type_ + ": " + id_);

   auto N = -randomProfile_s.generate(R0_s);

   auto pText = std::make_shared<GenText>(
      id_ + ".txt", "What is the binary notation for " + std::to_string(N) +
                       " in 8 bits 2-complement notation?");
   addToStem(pText);

   auto pO1 = std::make_shared<GenOption>(id_ + ".O1", util::Binary(N - 1, 8));
   auto pO2 = std::make_shared<GenOption>(id_ + ".O2", util::Binary(N, 8));
   auto pO3 = std::make_shared<GenOption>(id_ + ".O3", util::Binary(N + 1, 8));
   auto pO4 =
      std::make_shared<GenOption>(id_ + ".O4", util::Binary(128 + abs(N), 8));

   addToOptions(pO1);
   addToOptions(pO2, true);
   addToOptions(pO3);
   addToOptions(pO4);
   shuffleON();
   GenItem::prepare();
}
