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
class GenLogicExprAON : public GenItem
{
public:
   GenLogicExprAON();
   virtual ~GenLogicExprAON() = default;

   // virtual IGenPtr_t copy() const;
   // virtual std::ostream& write(std::ostream& os, int Level = 0) const;

protected:
   virtual void prepare() override;
   // virtual void generateContents(std::ostream& os);

private:
   static std::tuple<Random::range_t, int, std::list<int>, int> R0_s;

   static int correctAnswer(int OrAnd, int EqNot, int XorOr);

   std::shared_ptr<GenText> pText_;
   std::shared_ptr<GenCodeText> codeText_;
   std::shared_ptr<GenOption> pO1_;
   std::shared_ptr<GenOption> pO2_;
   std::shared_ptr<GenOption> pO3_;
   std::shared_ptr<GenOption> pO4_;

   int AON_;

   util::bool2Pars_t andF_;
   util::bool2Pars_t orF_;
   util::bool1Pars_t notF_;
   util::bool1Pars_t equF_;

   bool and_(bool b1, bool b2) { return b1 && b2; }
   bool or_(bool b1, bool b2) { return b1 || b2; }
   bool not_(bool b1) { return !b1; }
   bool equ_(bool b1) { return b1; }

   bool logicD_(bool b1, bool b2, bool b3);
};

#endif
