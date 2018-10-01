#ifndef RANDOM_H
#define RANDOM_H

#include "Log.h"

#include <boost/random.hpp>
#include <boost/random/uniform_int.hpp>

/// Random generator class based on boost::random.
/// Generates uniformly distributed integer values in the range 0..N.
class Random
{
private:
   unsigned long int seed_;
   boost::uniform_int<int> uniformInt_;
   boost::mt19937 mt19937_;

public:
   using range_t = std::pair<int, int>;
   /// Uniformly distributed integers in the range 0..N (N included).
   /// The seed is determined by time().
   Random(int N);
   /// Uniformly distributed integers in the range 0..N (N included).
   /// The seed value is determined by the parameter seed.
   Random(int N, unsigned long seed);
   virtual ~Random() = default;
   /// Random values generating function.
   boost::variate_generator<boost::mt19937, boost::uniform_int<int>> generate;
   /// For algorithm usage, example: Random rnd(10);
   /// std::random_shuffle(myvector.begin(), myvector.end(), rnd);
   std::ptrdiff_t operator()(std::ptrdiff_t arg)
   {
      LOGD("arg = " + std::to_string(arg));
      return static_cast<std::ptrdiff_t>(generate());
   }
};

#endif
