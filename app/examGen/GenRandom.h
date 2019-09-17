#ifndef GENRANDOM_H
#define GENRANDOM_H

#include "Seed.h"

#include <random>

/// Responsible for generating pseudo random integer values
/// in a range [min, max).
class GenRandom final
{
public:
   GenRandom(int incr = 0) { prnEng_.seed(getSeed() + incr); }
   /// Returns min <= random value < max, range [min, max)
   /// \pre max > min
   int generate(int max, int min = 0) { return prnEng_() % (max - min) + min; }

private:
   /// Standard pseudo-random number engine, reproducable, portable
   std::minstd_rand prnEng_;
};

#endif
