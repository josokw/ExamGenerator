#ifndef GENSTEM_H
#define GENSTEM_H

#include "GenComposite.h"
#include "IGenerator.h"

#include <string>
#include <vector>

class GenStem : public GenComposite
{
public:
   GenStem();
   virtual ~GenStem();

   virtual IGenPtr_t copy() const override;
   virtual void add(IGenPtr_t pGen) override;
   virtual void generate(std::ostream &os) override;
   virtual std::ostream &write(std::ostream &os, int level = 0) const override;

   void add(int index);

private:
   int index_;
};

#endif
