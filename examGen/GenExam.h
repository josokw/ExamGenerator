#ifndef GENEXAM_H
#define GENEXAM_H

#include "ICompositeGenerator.h"

#include <string>
#include <tuple>
#include <vector>

class GenHeader;
class GenItem;
class GenSolution;
class GenText;
class GenJava;

typedef std::tuple<char, int, const char *, std::string> message_t;

/// Generator for a exam, contains all kind of other generators (according to
/// composite pattern).
class GenExam : public ICompositeGenerator
{
public:
   GenExam(const std::string &id, std::vector<message_t> &messages);
   // GenExam(const GenExam &other) = default;
   virtual ~GenExam();

   IGenPtr_t copy() const override;
   void add(IGenPtr_t pGen) override;
   void generate(std::ostream &os) override;
   std::ostream &write(std::ostream &os, int level = 0) const override;

   IGenPtr_t getHeader() const
   {
      return (headerIsAdded_) ? generators_[headerIndex_] : nullptr;
   }
   void setLastItem();

private:
   static int nExams_s;
   std::vector<message_t> &messages_;
   bool headerIsAdded_;
   int headerIndex_;
   std::shared_ptr<GenItem> pLastAddedItem_;
   int indexLastAddedItem_;
   std::shared_ptr<GenSolution> pGenSolution_;
};

#endif
