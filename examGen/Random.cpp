#include "Random.h"
#include "Log.h"

#include <ctime>

Random::Random(int N)
   : seed_{static_cast<unsigned long>(std::time(nullptr))}
   , uniformInt_{0, N}
   , mt19937_{seed_}
   , generate(mt19937_, uniformInt_)
{
   LOGD("initialised, N = " + std::to_string(N) +
        " seed = " + std::to_string(seed_));
}

Random::Random(int N, unsigned long seed)
   : seed_{seed}
   , uniformInt_(0, N)
   , mt19937_(seed_)
   , generate(mt19937_, uniformInt_)
{
   LOGD("initialised, N = " + std::to_string(N) +
        " seed = " + std::to_string(seed_));
}
