#ifndef SEED_H
#define SEED_H

#include <cstdint>

inline uint_fast32_t seed;

inline void setSeed(uint_fast32_t sd)
{
   seed = sd;
}

inline uint_fast32_t getSeed()
{
   return seed;
}

#endif
