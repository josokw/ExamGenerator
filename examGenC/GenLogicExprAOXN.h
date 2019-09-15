#ifndef GENLOGICEXPRAOXN_H
#define GENLOGICEXPRAOXN_H

#include "GenItem.h"
#include "Util.h"

#include <list>
#include <tuple>

/// Resposible for creating a logic expression containing AND, OR, XOR and NOT
/// operators.
/// The options are formatted in 4 columns containing the truth tables.
class GenLogicExprAOXN final : public GenItem
{
public:
   GenLogicExprAOXN();
   virtual ~GenLogicExprAOXN() = default;

protected:
   void prepare() override;

private:
   static std::tuple<RandomProfile::range_t, int, std::list<int>, int> R0_s;
   static int correctAnswer(int OrAnd, int EqNot, int XorOr);
   int AOXN_;
   bool logicExpr(bool b1, bool b2, bool b3);
};

#endif
