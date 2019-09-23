#include "RandomProfile.h"
#include "Log.h"
#include "Seed.h"

#include <algorithm>
#include <cmath>
#include <list>

RandomProfile::RandomProfile()
   : genrnd_{getSeed()}
{
   LOGD(", initialised, seed = " + std::to_string(seed), 2);
}

RandomProfile::RandomProfile(unsigned long sd)
   : genrnd_{sd}
{
   LOGD(", initialised, seed = " + std::to_string(seed), 2);
}

void RandomProfile::generate(const std::vector<RandomProfile::range_t> &ranges)
{
   LOGD("", 3);

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

   LOGD("result = " + std::to_string(result), 3);
}

int RandomProfile::generate(const RandomProfile::range_t &range)
{
   int result{genrnd_.generate(range.second, range.first)};

   LOGD("Random value (in range " + std::to_string(range.first) + "-" +
           std::to_string(range.second) + ") = " + std::to_string(result),
        3);

   return result;
}

int RandomProfile::generate(fullR_t &fullR)
{
   int result = generate(std::get<0>(fullR));
   int historyDepth = std::get<3>(fullR);
   int historySize = std::get<2>(fullR).size();

   LOGI("historyDepth = " + std::to_string(historyDepth) +
        " historySize = " + std::to_string(historySize));

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

   LOGI("Random value (fullR) = " + std::to_string(result));

   return result;
}
