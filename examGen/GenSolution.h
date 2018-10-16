#ifndef GENSOLUTION_H
#define GENSOLUTION_H

#include "IGenerator.h"

#include <string>
#include <vector>

class GenExam;

/// Generates solution, reads all options from every item and collects the
/// correct answers.
class GenSolution : public IGenerator
{
public:
   GenSolution(GenExam *pExam);
   virtual ~GenSolution() = default;

   IGenPtr_t copy() const override;
   std::ostream &write(std::ostream &os, int level) const override;
   void prepare() override;
   void generate(std::ostream &os) override;

private:
   GenExam *pExam_;
   std::vector<int> solutions_;
};

#endif
