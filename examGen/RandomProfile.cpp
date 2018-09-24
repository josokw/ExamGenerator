#include "RandomProfile.h"
#include "Log.h"

#include <algorithm>
#include <cmath>
#include <list>

RandomProfile::RandomProfile()
   : random0_1_{1}
   , random0_2_{2}
   , random0_3_(3)
   , random0_4_{4}
   , random0_5_{5}
   , random0_6_{6}
   , random0_7_{7}
   , random0_8_{8}
   , random0_9_{9}
{
   LOGD(", initialised");
}

RandomProfile::RandomProfile(unsigned long seed)
   : random0_1_{1, seed}
   , random0_2_{2, seed}
   , random0_3_{3, seed}
   , random0_4_{4, seed}
   , random0_5_{5, seed}
   , random0_6_{6, seed}
   , random0_7_{7, seed}
   , random0_8_{8, seed}
   , random0_9_{9, seed}
{
   LOGD(", initialised, seed = " + std::to_string(seed));
}

void RandomProfile::generate(const std::vector<Random::range_t> &ranges)
{
   LOGD("");

   profile_.clear();
   for (auto &r : ranges) {
      profile_.push_back(generate(r));
   }
   //    auto ciRanges = cbegin(ranges);
   //    while (ciRanges != ranges.end()) {
   //       profile_.push_back(generate(*ciRanges));
   //       ++ciRanges;
   //    }
}

void RandomProfile::generate(std::vector<fullR_t> &fullRs)
{
   int result = generate(std::get<0>(fullRs[0]));
   
   LOGD("result = " + std::to_string(result));
}

int RandomProfile::generate(const Random::range_t &range)
{
   int result = 0;
   int rangeWidth = abs(range.second - range.first);

   switch (rangeWidth) {
      case 1:
         result = random0_1_.generate() + range.first;
         break;
      case 2:
         result = random0_2_.generate() + range.first;
         break;
      case 3:
         result = random0_3_.generate() + range.first;
         break;
      case 4:
         result = random0_4_.generate() + range.first;
         break;
      case 5:
         result = random0_5_.generate() + range.first;
         break;
      case 6:
         result = random0_6_.generate() + range.first;
         break;
      case 7:
         result = random0_7_.generate() + range.first;
         break;
      case 8:
         result = random0_8_.generate() + range.first;
         break;
      case 9:
         result = random0_9_.generate() + range.first;
         break;
      default:
         // throw
         break;
   }

   LOGD("Random value (range) = " + std::to_string(result));

   return result;
}

int RandomProfile::generate(fullR_t &fullR)
{
   int result = generate(std::get<0>(fullR));
   int historyDepth = std::get<3>(fullR);
   int historySize = std::get<2>(fullR).size();

   historyDepth = std::min(historyDepth, historySize);
   if (historyDepth > 0) {
      bool isAlreadyGenerated = false;

      std::list<int>::iterator iLi = std::get<2>(fullR).begin();
      int hd = historyDepth;
      while (hd > 0) {
         ++iLi;
         --hd;
      }
      while (std::search_n(std::get<2>(fullR).begin(), iLi, 1, result) != iLi) {
         result = generate(std::get<0>(fullR));
      }
   }
   std::get<1>(fullR) = result;
   std::get<2>(fullR).push_front(result);

   LOGD("Random value (fullR) = " + std::to_string(result));

   return result;
}
