#ifndef GENNULL_H
#define GENNULL_H

#include "IGenerator.h"

/// A class according to the Null Object Pattern.
/// All methods do nothing: defined neutral behavior,
/// gives consistent and predictable behavior for the null situation.
///
/// Class invariant: TRUE
class GenNull : public IGenerator
{
public:
   static const GenNull GEN_NULL();

   GenNull();
   virtual ~GenNull() = default;

   virtual IGenPtr_t copy() const override;
   virtual void generate(std::ostream &os) override;
   virtual std::ostream &write(std::ostream &os, int level = 0) const override;
};

#endif
