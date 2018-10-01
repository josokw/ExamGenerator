#ifndef GENNESTEDFOR_H
#define GENNESTEDFOR_H

#include "GenItem.h"

#include <tuple>

class GenStem;
class GenText;
class GenCodeText;
class GenOption;

class GenNestedFor : public GenItem
{
public:
   GenNestedFor();
   virtual ~GenNestedFor() = default;

   // virtual IGenPtr_t copy();
   // virtual void prepare();
   // virtual void generate(std::ostream& os);
   // virtual std::ostream& write(std::ostream& os, int Level = 0) const;

protected:
   virtual void prepare();
   // virtual void generateContents(std::ostream& os);

private:
   static std::tuple<Random::range_t, int, std::list<int>, int> s_R0;
   static std::tuple<Random::range_t, int, std::list<int>, int> s_R1;
   static std::tuple<Random::range_t, int, std::list<int>, int> s_R2;

   static int correctAnswer(int InitValue, int iStart, int jStart, int iMax,
                            int jMax);

   std::shared_ptr<GenText> m_pText;
   std::shared_ptr<GenCodeText> m_pCodeText;
   std::shared_ptr<GenOption> m_pO1;
   std::shared_ptr<GenOption> m_pO2;
   std::shared_ptr<GenOption> m_pO3;
   std::shared_ptr<GenOption> m_pO4;
};

#endif
