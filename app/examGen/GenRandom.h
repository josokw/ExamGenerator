#ifndef GENRANDOM_H
#define GENRANDOM_H

#include "AppInfo.h"
#include "Seed.h"

#include <random>
#include <string>

/// Responsible for generating pseudo random integer values
/// in a range [min, max).
class GenRandom final
{
public:
   GenRandom(int incr = 0) { prnEng_.seed(getSeed() + incr); }
   /// Returns min <= random value < max, range [min, max)
   /// \pre max > min
   int generate(int max, int min = 0)
   {
      auto rnd = prnEng_() % (max - min) + min;
      rDNA_s += "-" + std::to_string(rnd);
      return rnd;
   }

   static const std::string &rDNA() { return rDNA_s; }

private:
   inline static std::string rDNA_s{"rDNA-" VERSION};
   /// Standard pseudo-random number engine, reproducible, portable
   std::minstd_rand prnEng_;
};

#endif
