#ifndef GENEXAM_H
#define GENEXAM_H

#include "GenComposite.h"

#include <vector>
#include <tuple>
#include <string>

class GenHeader;
class GenItem;
class GenSolution;
class GenText;
class GenJava;

typedef std::tuple<char, int, const char*, std::string> message_t;

/// Generator for a exam, contains all kind of other generators (according to
/// composite pattern).
class GenExam : public GenComposite
{
public:
   GenExam(std::vector<message_t> &messages);
   virtual ~GenExam();

   virtual IGenPtr_t copy() const override;
   virtual void add(IGenPtr_t pGen) override;
   virtual std::ostream &write(std::ostream &os, int Level = 0) const override;

   void setLastItem();
   virtual void generate(std::ostream &os) override;

private:
   static int nExams_s;
   std::vector<message_t> &messages;
   bool HeaderIsAdded;
   std::shared_ptr<GenItem> pLastAddedItem;
   int indexLastAddedItem;
   std::shared_ptr<GenSolution> pGenSolution;
};

#endif
