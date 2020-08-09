#ifndef GENEXAM_H
#define GENEXAM_H

#include "ICompositeGenerator.h"

#include <string>
#include <tuple>
#include <vector>

class GenItem;
class GenSolution;

typedef std::tuple<char, int, const char *, std::string> message_t;

/// Generator for a exam, contains all kind of other generators (according to
/// composite pattern).
class GenExam : public ICompositeGenerator
{
public:
   GenExam(std::string_view id, std::vector<message_t> &messages);
   ~GenExam() override;

   [[nodiscard]] IGenPtr_t copy() const override;
   void add(IGenPtr_t pGen) override;
   void generate(std::ostream &os) override;
   std::ostream &write(std::ostream &os, int level = 0) const override;

   [[nodiscard]] IGenPtr_t getHeader() const {
      return (headerIsAdded_) ? generators_[headerIndex_] : nullptr;
   } void setLastItem();

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
