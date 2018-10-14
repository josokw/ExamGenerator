#ifndef GENLOGICEXPRAOXN_H
#define GENLOGICEXPRAOXN_H

#include "GenItem.h"
#include "Util.h"

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <list>
#include <tuple>

class GenStem;
class GenText;
class GenCodeText;
class GenOption;

/// Resposible for creating a logic expression containing AND, OR, XOR and NOT
/// blocks. The options are formatted in 4 columns containing the truth tables.
///
/// @todo Replace logic diagram by C logical expression.
class GenLogicExprAOXN : public GenItem
{
public:
   GenLogicExprAOXN();
   virtual ~GenLogicExprAOXN() = default;

   // virtual IGenPtr_t copy();
   // virtual std::ostream& write(std::ostream& os, int Level = 0) const;

protected:
   virtual void prepare();
   // virtual void generateContents(std::ostream& os);

private:
   static std::tuple<Random::range_t, int, std::list<int>, int> s_R0;
   static int correctAnswer(int OrAnd, int EqNot, int XorOr);

   std::shared_ptr<GenText> m_pText;
   std::shared_ptr<GenOption> m_pO1;
   std::shared_ptr<GenOption> m_pO2;
   std::shared_ptr<GenOption> m_pO3;
   std::shared_ptr<GenOption> m_pO4;

   int m_AON;

   GenLogicExprAOXN *self() { return this; }

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

   bool logicD(bool b1, bool b2, bool b3);
};

#endif