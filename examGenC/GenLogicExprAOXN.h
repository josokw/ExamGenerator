#ifndef GENLOGICEXPRAOXN_H
#define GENLOGICEXPRAOXN_H

#include "GenItem.h"
#include "Util.h"

#include <list>
#include <tuple>

/// Resposible for creating a logic expression containing AND, OR, XOR and NOT
/// blocks. The options are formatted in 4 columns containing the truth tables.
class GenLogicExprAOXN : public GenItem
{
public:
   GenLogicExprAOXN();
   virtual ~GenLogicExprAOXN() = default;

protected:
   virtual void prepare() override;

private:
   static std::tuple<Random::range_t, int, std::list<int>, int> R0_s;
   static int correctAnswer(int OrAnd, int EqNot, int XorOr);

   int AOXN_;

   util::bool2Pars_t andF;
   util::bool2Pars_t orF;
   util::bool2Pars_t xorF;
   util::bool1Pars_t notF;
   util::bool1Pars_t equF;

   bool and_(bool b1, bool b2) { return b1 && b2; }
   bool or_(bool b1, bool b2) { return b1 || b2; }
   bool xor_(bool b1, bool b2) { return b1 ^ b2; }
   bool not_(bool b1) { return !b1; }
   bool equ(bool b1) { return b1; }

   bool logicExpr(bool b1, bool b2, bool b3);
};

#endif
