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

   std::shared_ptr<GenText> m_pText;
   std::shared_ptr<GenCodeText> m_pJava;
   std::shared_ptr<GenOption> m_pO1;
   std::shared_ptr<GenOption> m_pO2;
   std::shared_ptr<GenOption> m_pO3;
   std::shared_ptr<GenOption> m_pO4;

   int N_;
   std::string binaryN_;
};

#endif