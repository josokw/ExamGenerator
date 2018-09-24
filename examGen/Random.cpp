#include "Random.h"
#include "Log.h"

#include <ctime>

Random::Random(int N)
   : m_UniformInt(0, N)
   , m_Mt(static_cast<unsigned long>(std::time(0)))
   , generate(m_Mt, m_UniformInt)
{
   LOGD("initialised, N = " + std::to_string(N) +
        " seed = " + std::to_string(seed_));
}

Random::Random(int N, unsigned long seed)
   : m_UniformInt(0, N)
   , m_Mt(seed)
   , generate(m_Mt, m_UniformInt)
{
   LOGD("initialised, N = " + std::to_string(N) +
        " seed = " + std::to_string(seed_));
}
