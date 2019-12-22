#ifndef GENSELECTOR_H
#define GENSELECTOR_H

#include "ICompositeGenerator.h"

#include <iostream>
#include <vector>

/// Specialized composite generator class, aggregates 0..n other generator
/// objects (instantiations of IGenerator derived classes).
/// Supports random selection of a number of aggregated generator objects.
///
/// Class invariant: ??
class GenSelector : public ICompositeGenerator
{
public:
   GenSelector();
   GenSelector(const std::string &id);
   ~GenSelector() override = default;

   [[nodiscard]] IGenPtr_t copy() const override;
   void add(IGenPtr_t pGen) override;
   // virtual void generate(std::ostream& os);
   std::ostream &write(std::ostream &os, int level = 0) const override;

   [[nodiscard]] int sizeAll() const { return allGenerators_.size(); }
   void selectR(unsigned int n);

protected:
   std::vector<IGenPtr_t> allGenerators_;
};

#endif
