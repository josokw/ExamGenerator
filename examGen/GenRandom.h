#ifndef GENRANDOM_H
#define GENRANDOM_H

#include "Seed.h"

#include <random>

/// Reposible for generating pseudo random integer values
/// in a range [min, max).
class GenRandom
{
public:
   using range_t = std::pair<int, int>;

   GenRandom(int incr = 0) { eng.seed(getSeed() + incr); }
   /// Returns min <= random value < max, range [min, max)
   /// \pre max > min
   int generate(int max, int min = 0) { return eng() % (max - min) + min; }

private:
   /// Standard pseudo-random number engine, reproducable, portable
   std::minstd_rand eng;
};

#endif
