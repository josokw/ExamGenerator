#ifndef GENEXAMS_H
#define GENEXAMS_H

#include "ICompositeGenerator.h"
#include "Reader.h"

#include <vector>

/// Generator for a set of exams. Contains 1 or more pointers to #GenExam
/// objects.
class GenExams : public ICompositeGenerator
{
public:
   GenExams(std::string_view id, std::vector<Reader::message_t> &messages,
            int nExams = 1);
   ~GenExams() override = default;

   void add(IGenPtr_t pGen) override;
   void generate(std::ostream &os) override;
   std::ostream &write(std::ostream &os, int Level = 0) const override;
   void setID(std::string_view id);

private:
   virtual IGenPtr_t copy() const { return nullptr; }
};

#endif
