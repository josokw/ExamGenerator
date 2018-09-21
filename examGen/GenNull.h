#ifndef GENNULL_H
#define GENNULL_H

#include <string>

#include "IGenerator.h"

/// A class according to the Null Object Pattern.
/// All methods do nothing: defined neutral behavior,
/// gives consistent and predictable behavior for the null situation.
///
/// Class invariant: TRUE
class GenNULL : public IGenerator
{
public:
   static const GenNULL GEN_NULL();

   GenNULL();
   virtual ~GenNULL() = default;

   virtual IGenPtr_t copy() const;
   virtual void generate(std::ostream &os);
   virtual std::ostream &write(std::ostream &os, int level = 0) const;
};

#endif
