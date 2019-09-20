#include "GenCodeText.h"
#include "Log.h"
#include "Util.h"

#include <string>

GenCodeText::GenCodeText(const std::string &id,
                         const std::string &programmingLanguage,
                         const std::string &codeText)
   : ILeafGenerator{id}
   , programmingLanguage_{programmingLanguage}
   , codeText_{codeText}
{
   type_ = __func__;

   LOGD(id_ + " initialised", 2);
}

IGenPtr_t GenCodeText::copy() const
{
   std::unique_ptr<GenCodeText> p(new GenCodeText(*this));
   return p;
}

void GenCodeText::generate(std::ostream &os)
{
   auto context = util::removeNewLines(util::limitSize(codeText_, 60));
   LOGD(type_ + ": " + id_ + ", '" + programmingLanguage_ +
        "' code text = " + context, 3);

   os << "\\lstset{ language = " << programmingLanguage_ << "}\n"
      << "\\begin{lstlisting}\n"
      << codeText_ << " \n"
      << "\\end{lstlisting}\n";
}

std::ostream &GenCodeText::write(std::ostream &os, int Level) const
{
   IGenerator::write(os, Level);
   os << ": " << programmingLanguage_ << "  " << codeText_.substr(0, 5)
      << "...\n";

   return os;
}
