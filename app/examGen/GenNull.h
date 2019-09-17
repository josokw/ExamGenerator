#ifndef GENNULL_H
#define GENNULL_H

#include "ILeafGenerator.h"

/// A class according to the Null Object Pattern.
/// All methods do nothing: defined neutral behavior,
/// gives consistent and predictable behavior for the null situation.
///
/// Class invariant: TRUE
class GenNull : public ILeafGenerator
{
public:
   GenNull();
   virtual ~GenNull() = default;

   IGenPtr_t copy() const override;
   void generate(std::ostream &os) override;
   std::ostream &write(std::ostream &os, int level = 0) const override;
};

#endif
