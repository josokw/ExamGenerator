#include <string>

#include "GenText.h"
#include "Log.h"

using namespace std;

GenText::GenText(const std::string &text)
   : IGenerator{}
   , text_{text}
{
   type_ = "GenText";
   LOGD(id_ + ", initialised");
}

IGenPtr_t GenText::copy() const
{
   std::shared_ptr<GenText> p(new GenText(*this));
   return p;
}

std::ostream &GenText::write(std::ostream &os, int Level) const
{
   IGenerator::write(os, Level);
   os << ": " << text_.substr(0, 25) << "...\n";
   return os;
}

void GenText::generate(std::ostream &os)
{
   LOGD(type_ + ": " + id_ + ", text = " + text_.substr(0, 15) + "...");
   os << '{' << text_ << '}';
}
