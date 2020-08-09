
#include "GenText.h"
#include "Log.h"

#include <string>

GenText::GenText(std::string_view id, std::string_view text)
   : ILeafGenerator{id}
   , text_{text}
{
   type_ = __func__;

   LOGD("'" + id_ + "', initialised", 2);
}

IGenPtr_t GenText::copy() const
{
   std::shared_ptr<GenText> p(new GenText(*this));
   return p;
}

std::ostream &GenText::write(std::ostream &os, int level) const
{
   IGenerator::write(os, level);
   os << ": " << text_.substr(0, 25) << "...\n";
   return os;
}

void GenText::generate(std::ostream &os)
{
   LOGD(type_ + ": '" + id_ + "' = " + text_.substr(0, 20) + "...", 3);

   os << '{' << text_ << '}';
}
