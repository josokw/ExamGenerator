#ifndef ICOMPOSITEGENERATOR_H
#define ICOMPOSITEGENERATOR_H

#include "IGenerator.h"

#include <string>
#include <vector>

/// Abstract base class for composite generators, aggregates pointers
/// to 0..n other generator objects (instantiations of #IGenerator derived
/// classes). According to composite design pattern.
///
/// Class invariant: #generators_ contains no null pointers.
class ICompositeGenerator : public IGenerator
{
public:
   ICompositeGenerator();
   explicit ICompositeGenerator(const std::string &id);
   ~ICompositeGenerator() override = default;
   //    ICompositeGenerator(const ICompositeGenerator &other) = delete;
   //    ICompositeGenerator &operator=(ICompositeGenerator &other) = delete;

   void generate(std::ostream &os) override;
   std::ostream &write(std::ostream &os, int level = 0) const override;

   [[nodiscard]] IGenPtr_t operator[](int index)
   {
      return generators_.at(index);
   }
   [[nodiscard]] std::vector<IGenPtr_t> &getGenerators() {
      return generators_;
   }
   [[nodiscard]] const std::vector<IGenPtr_t> &getGenerators() const
   {
      return generators_;
   }
   [[nodiscard]] size_t size() const { return generators_.size(); } void clear()
   {
      generators_.clear();
   }

protected:
   std::vector<IGenPtr_t> generators_;

   bool generatorsCheck() const;
};

#endif
