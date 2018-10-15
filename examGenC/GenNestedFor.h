#ifndef GENNESTEDFOR_H
#define GENNESTEDFOR_H

#include "GenItem.h"

#include <tuple>

class GenStem;
class GenText;
class GenCodeText;
class GenOption;

/// Generates a nested for loop.
class GenNestedFor : public GenItem
{
public:
   GenNestedFor();
   virtual ~GenNestedFor() = default;

protected:
   virtual void prepare() override;

private:
   static std::tuple<Random::range_t, int, std::list<int>, int> s_R0;
   static std::tuple<Random::range_t, int, std::list<int>, int> s_R1;
   static std::tuple<Random::range_t, int, std::list<int>, int> s_R2;

   static int correctAnswer(int initResult, int iStart, int jStart, int iMax,
                            int jMax);
};

#endif
