#ifndef RANDOMPROFILE_H
#define RANDOMPROFILE_H

#include "Random.h"
#include <list>
#include <tuple>
#include <vector>

/// Responsible for generating a random profile containing a number of integer
/// values based on range information. Maximum range width: 9. Range (closed
/// interval): [N .. max 9+N]. Examples: [3..7] [3..12] [88..90]. Uses the class
/// #Random to generate uniformly distributed profile data.
class RandomProfile
{
public:
   using profile_t = std::vector<int>;
   using fullR_t = std::tuple<Random::range_t, int, std::list<int>, int>;

   RandomProfile();
   RandomProfile(unsigned long seed);
   virtual ~RandomProfile() = default;

   void generate(const std::vector<Random::range_t> &Ranges);
   void generate(std::vector<fullR_t> &fullRs);
   const RandomProfile::profile_t &getProfile() const { return profile_; }

private:
   /// Random generators for different ranges
   Random random0_1_;
   Random random0_2_;
   Random random0_3_;
   Random random0_4_;
   Random random0_5_;
   Random random0_6_;
   Random random0_7_;
   Random random0_8_;
   Random random0_9_;
   /// Random generated profile data
   profile_t profile_;

public:
   /// generates 1 random value acoording to Range data
   int generate(const Random::range_t &range);
   /// generates 1 random value acoording to fullR data
   int generate(fullR_t &fullR);
};

#endif
