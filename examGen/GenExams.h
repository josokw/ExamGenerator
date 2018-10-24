#ifndef GENEXAMS_H
#define GENEXAMS_H

#include "GenComposite.h"
#include "Reader.h"

#include <vector>

/// Generator for a set of exams. Contains 1 or more #GenExam objects.
class GenExams : public GenComposite
{
public:
   GenExams(const std::string &id, std::vector<Reader::message_t> &messages,
            int nTests = 1);
   virtual ~GenExams() = default;

   void add(IGenPtr_t pGen) override;
   void generate(std::ostream &os) override;
   std::ostream &write(std::ostream &os, int Level = 0) const override;

   void setID(const std::string &id);

private:
   virtual IGenPtr_t copy() const { return NULL; }
};

#endif
