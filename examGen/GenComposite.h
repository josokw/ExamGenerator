#ifndef GENCOMPOSITE_H
#define GENCOMPOSITE_H

#include <iostream>
#include <vector>

#include "IGenerator.h"

/// Composite generator class (abstract base class), aggregates pointers
/// to 0..n other generator objects (instantiations of #IGenerator derived
/// classes). According to composite design pattern.
///
/// Class invariant: #generators_ contains no null pointers.
class GenComposite : public IGenerator
{
public:
   GenComposite();
   GenComposite(const std::string &id);
   GenComposite(const GenComposite &other) = default;
   virtual ~GenComposite() = default;

   virtual IGenPtr_t copy() const = 0;
   virtual void add(IGenPtr_t pGen);
   virtual void generate(std::ostream &os) override;
   virtual std::ostream &write(std::ostream &os, int level = 0) const override;

   IGenPtr_t operator[](int index) { return generators_.at(index); }
   std::vector<IGenPtr_t> &getGenerators() { return generators_; }
   const std::vector<IGenPtr_t> &getGenerators() const { return generators_; }
   size_t size() const { return generators_.size(); }
   void clear() { generators_.clear(); }

protected:
   std::vector<IGenPtr_t> generators_;

   bool generatorsCheck() const;
};

#endif
