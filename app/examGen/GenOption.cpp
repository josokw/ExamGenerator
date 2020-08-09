#include "GenOption.h"
#include "GenCodeText.h"
#include "GenText.h"
#include "Log.h"
#include "Util.h"

#include <string>

GenOption::GenOption(std::string_view id, std::string_view text)
   : ICompositeGenerator{id}
   , isCorrect_{false}
   , text_{text}
{
   type_ = __func__;

   LOGD("'" + id_ + "', initialised", 2);
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
   LOGD(type_ + ": " + id_ + ", wants to add " + pGen->getType() + " '" +
           pGen->getID() + "'",
        3);

   if (std::shared_ptr<GenText> pText =
          std::dynamic_pointer_cast<GenText>(pGen)) {
      generators_.push_back(pGen);
   } else {
      if (std::shared_ptr<GenCodeText> pCodeText =
             std::dynamic_pointer_cast<GenCodeText>(pGen)) {
         generators_.push_back(pGen);
      } else {
         LOGE("'" + id_ + "',  " + pGen->getType() + " not allowed for adding");
      }
   }
}

void GenOption::generate(std::ostream &os)
{
   auto context = util::removeNewLines(util::limitSize(text_, 60));
   LOGD(type_ + ": '" + id_ + "' = " + context + " ...", 3);

   if (text_.empty()) {
      os << ".\\\\[-1.0cm]\n";
   } else {
      os << text_ << "\n";
   }
   ICompositeGenerator::generate(os);
}

std::ostream &GenOption::write(std::ostream &os, int level) const
{
   auto context = util::removeNewLines(util::limitSize(text_, 60));

   IGenerator::write(os, level);
   os << ": " << context << "  correct = " << isCorrect_ << "\n";
   ICompositeGenerator::write(os, level + 1);

   return os;
}
