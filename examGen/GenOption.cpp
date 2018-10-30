#include "GenCodeText.h"
#include "GenOption.h"
#include "GenText.h"
#include "Log.h"

#include <string>

GenOption::GenOption(const std::string &id, const std::string &text)
   : ICompositeGenerator{id}
   , isCorrect_{false}
   , text_{text}
{
   type_ = "GenOption";

   LOGD(id_ + ", initialised");
}

IGenPtr_t GenOption::copy() const
{
   std::shared_ptr<GenOption> p(new GenOption(*this));
   for_each(p->generators_.begin(), p->generators_.end(),
            [](IGenPtr_t &pGen) { pGen = pGen->copy(); });
   return p;
}

void GenOption::add(IGenPtr_t pGen)
{
   LOGD(type_ + ": " + id_ + ", want to add " + pGen->getType() + " " +
        pGen->getID());

   if (std::shared_ptr<GenText> pText =
          std::dynamic_pointer_cast<GenText>(pGen)) {
      generators_.push_back(pGen);
   } else {
      if (std::shared_ptr<GenCodeText> pCodeText =
             std::dynamic_pointer_cast<GenCodeText>(pGen)) {
         generators_.push_back(pGen);
      } else {
         LOGE(id_ + ",  " + pGen->getType() + " not allowed for adding");
      }
   }
}

void GenOption::generate(std::ostream &os)
{
   LOGD(type_ + ": " + id_ + ", " + text_.substr(0, 15) + " ...");

   os << text_ << "\n";
   ICompositeGenerator::generate(os);
}

std::ostream &GenOption::write(std::ostream &os, int level) const
{
   IGenerator::write(os, level);
   if (text_.size() < 20) {
      os << ": " << text_.substr(0, 20) << "  correct = " << isCorrect_ << "\n";
   } else {
      os << ": " << text_.substr(0, 20) << "...  correct = " << isCorrect_
         << "\n";
   }
   ICompositeGenerator::write(os, level + 1);

   return os;
}
