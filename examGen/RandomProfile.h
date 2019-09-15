#ifndef RANDOMPROFILE_H
#define RANDOMPROFILE_H

//#include "Random.h"
#include "GenRandom.h"

#include <list>
#include <tuple>
#include <vector>

/// Responsible for generating a random profile containing a number of integer
/// values based on range information. Maximum range width: 9. Range (closed
/// interval): [N .. max 9+N]. Examples: [3..7] [3..12] [88..90]. 
/// Uses the class #GenRandom to generate pseudo random values.
class RandomProfile
{
public:
   using range_t = std::pair<int, int>;
   using profile_t = std::vector<int>;
   using fullR_t = std::tuple<RandomProfile::range_t, int, std::list<int>, int>;

   RandomProfile();
   RandomProfile(unsigned long sd);
   virtual ~RandomProfile() = default;

   void generate(const std::vector<RandomProfile::range_t> &Ranges);
   void generate(std::vector<fullR_t> &fullRs);
   const RandomProfile::profile_t &getProfile() const { return profile_; }

private:
   GenRandom genrnd_;
   /// Random generated profile data
   profile_t profile_;

public:
   /// generates 1 random value acoording to Range data
   int generate(const RandomProfile::range_t &range);
   /// generates 1 random value acoording to fullR data
   int generate(fullR_t &fullR);
};

#endif
