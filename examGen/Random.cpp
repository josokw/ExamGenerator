#include "Random.h"
#include "Log.h"

#include <ctime>

Random::Random(int N)
   : seed_{static_cast<unsigned long>(std::time(0))}
   , m_UniformInt{0, N}
   , mt19937_{seed_}
   , generate(mt19937_, m_UniformInt)
{
   LOGD("initialised, N = " + std::to_string(N) +
        " seed = " + std::to_string(seed_));
}

Random::Random(int N, unsigned long seed)
   : seed_{seed}
   , m_UniformInt(0, N)
   , mt19937_(seed_)
   , generate(mt19937_, m_UniformInt)
{
   LOGD("initialised, N = " + std::to_string(N) +
        " seed = " + std::to_string(seed_));
}
