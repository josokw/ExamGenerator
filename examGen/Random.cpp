#include "Random.h"
#include <ctime>

using namespace std;

Random::Random(int N)
   : m_Mt(static_cast<unsigned long>(std::time(0)))
   , m_UniformInt(0, N)
   , generate(m_Mt, m_UniformInt)
{
}

Random::Random(int N, unsigned long seed)
   : m_Mt(seed)
   , m_UniformInt(0, N)
   , generate(m_Mt, m_UniformInt)
{
}
