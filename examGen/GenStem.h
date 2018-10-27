#ifndef GENSTEM_H
#define GENSTEM_H

#include "ICompositeGenerator.h"

#include <string>
#include <vector>

class GenStem : public ICompositeGenerator
{
public:
   GenStem();
   virtual ~GenStem() = default;

   IGenPtr_t copy() const override;
   void add(IGenPtr_t pGen) override;
   void generate(std::ostream &os) override;
   std::ostream &write(std::ostream &os, int level = 0) const override;

   void add(int index);

private:
   int index_;
};

#endif
