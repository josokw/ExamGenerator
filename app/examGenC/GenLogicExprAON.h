#ifndef GENLOGICEXPRAON_H
#define GENLOGICEXPRAON_H

#include "GenItem.h"
#include "Util.h"

#include <list>
#include <tuple>

class GenStem;
class GenText;
class GenCodeText;
class GenOption;

/// Responsible for creating a logical expression containing the AND, OR, and
/// NOT operators.
/// The options are formatted in 4 columns containing the truth tables.
class GenLogicExprAON final : public GenItem
{
public:
   GenLogicExprAON();
   GenLogicExprAON(std::string_view id);
   virtual ~GenLogicExprAON() = default;

protected:
   void prepare() override;

private:
   static std::tuple<RandomProfile::range_t, int, std::list<int>, int> R0_s;
   static int correctAnswer(int OrAnd, int EqNot, int XorOr);
   int AON_;
   bool logicExpr(bool b1, bool b2, bool b3);
};

#endif
