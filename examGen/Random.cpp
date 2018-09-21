#include "Random.h"
#include <ctime>

using namespace std;

Random::Random(int N)
   : m_UniformInt(0, N)
   , m_Mt(static_cast<unsigned long>(std::time(0)))
   , generate(m_Mt, m_UniformInt)
{
}

Random::Random(int N, unsigned long seed)
   : m_UniformInt(0, N)
   , m_Mt(seed)
   , generate(m_Mt, m_UniformInt)
{
}
