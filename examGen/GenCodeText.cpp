#include <string>

#include "GenCodeText.h"
#include "Log.h"

GenCodeText::GenCodeText(const std::string &id,
                         const std::string &programmingLanguage,
                         const std::string &codeText)
   : IGenerator{id}
   , programmingLanguage_{programmingLanguage}
   , codeText_{codeText}
{
   type_ = "GenCodeText";
   LOGD(id_ + " initialised");
}

IGenPtr_t GenCodeText::copy() const
{
   std::unique_ptr<GenCodeText> p(new GenCodeText(*this));
   return p;
}

void GenCodeText::generate(std::ostream &os)
{
   LOGD(type_ + ": " + id_ + ", '" + programmingLanguage_ +
        "' code text = " + codeText_.substr(0, 20) + "...");

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
