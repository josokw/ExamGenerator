#ifndef GENOPTION_H
#define GENOPTION_H

#include "GenComposite.h"

#include <string>

class GenOption : public GenComposite
{
public:
   GenOption(const std::string &id, const std::string &text);
   virtual ~GenOption() = default;

   IGenPtr_t copy() const;
   void add(IGenPtr_t pGen) override;
   void generate(std::ostream &os) override;
   std::ostream &write(std::ostream &os, int level = 0) const override;

   bool getIsCorrect() const { return isCorrect_; }
   void setIsCorrect() const { isCorrect_ = true; }
   size_t size() const { return text_.size(); }

private:
   mutable bool isCorrect_;
   std::string text_;
};

#endif
