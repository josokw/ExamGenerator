#ifndef GENTWOC_H
#define GENTWOC_H

#include "GenItem.h"

#include <tuple>
#include <list>

class GenStem;
class GenText;
class GenCodeText;
class GenOption;

class GenTwoC : public GenItem
{
public:
   GenTwoC();
   virtual ~GenTwoC();

   // virtual IGenPtr_t copy();
   // virtual void generate(std::ostream& os);
   // virtual std::ostream& write(std::ostream& os, int Level = 0) const;

protected:
   virtual void prepare();
   // virtual void generateContents(std::ostream& os);

private:
   static std::tuple<Random::range_t, int, std::list<int>, int> s_R0;

   std::shared_ptr<GenText> pText_;
   std::shared_ptr<GenCodeText> pCode_;
   std::shared_ptr<GenOption> pO1_;
   std::shared_ptr<GenOption> pO2_;
   std::shared_ptr<GenOption> pO3_;
   std::shared_ptr<GenOption> pO4_;

   int N_;
   std::string binaryN_;
};

#endif