#ifndef GENNESTEDFOR_H
#define GENNESTEDFOR_H

#include "GenItem.h"

/// Generates a question about a nested for loop.
class GenNestedFor final : public GenItem
{
public:
   GenNestedFor(const std::string & id);
   virtual ~GenNestedFor() = default;

protected:
   void prepare() override;

private:
   static RandomProfile::fullR_t R0_s;
   static RandomProfile::fullR_t R1_s;
   static RandomProfile::fullR_t R2_s;

   static int correctAnswer(int initResult, int iStart, int jStart, int iMax,
                            int jMax);
};

#endif
