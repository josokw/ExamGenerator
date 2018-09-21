#ifndef GENSTEM_H
#define GENSTEM_H

#include "GenComposite.h"
#include "IGenerator.h"

#include <string>
#include <vector>

class GenText;
class GenCodeText;
class GenAPI;

class GenStem : public GenComposite
{
public:
   GenStem();
   virtual ~GenStem();

   virtual IGenPtr_t copy() const;
   virtual void add(IGenPtr_t pGen);
   virtual void generate(std::ostream &os);
   virtual std::ostream &write(std::ostream &os, int level = 0) const;

   void add(int index);

private:
   int index_;
};

#endif
