#include <string>

#include "GenCodeText.h"

using namespace std;

GenCodeText::GenCodeText(const std::string &programmingLanguage,
                         const std::string &codeText)
   : IGenerator()
   , programmingLanguage_{programmingLanguage}
   , codeText_{codeText}
{
   type_ = "GenCodeText";
}

GenCodeText::~GenCodeText()
{
   // IGenerator::write(clog) << " ##### DTOR" << endl;
}

IGenPtr_t GenCodeText::copy() const
{
   std::shared_ptr<GenCodeText> p(new GenCodeText(*this));
   return p;
}

void GenCodeText::generate(std::ostream &os)
{
   os << "\\lstset{ language = " << programmingLanguage_ << "}\n"
      << "\\begin{lstlisting}\n\n"
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
