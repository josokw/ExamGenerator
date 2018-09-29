#include <string>

#include "GenHeader.h"
#include "Log.h"

GenHeader::GenHeader()
   : IGenerator()
   , School("SCHOOL")
   , Course("Course")
   , Lecturer("Lecturer")
   , Date("Future")
   , BoxedText("")
{
   type_ = "GenHeader";
   LOGD("initialised");
}

GenHeader::GenHeader(const std::string &id)
   : IGenerator(id)
   , School("SCHOOL")
   , Course("Course")
   , Lecturer("Lecturer")
   , Date("Future")
   , BoxedText("")
{
   type_ = "GenHeader";
   LOGD(id_ + ", initialised");
}

GenHeader::~GenHeader()
{
   LOGD(id_);
}

IGenPtr_t GenHeader::copy() const
{
   std::shared_ptr<GenHeader> p(new GenHeader(*this));
   return p;
}

void GenHeader::generate(std::ostream &os)
{
   os << "\\noindent\n"
      << "\\textbf{\\LARGE " << School << "} \\newline \n"
      << "\\textbf{\\large Course: " << Course << "} \\\\* \n"
      << "\\textbf{\\large Lecturer(s): " << Lecturer << "} \\\\* \n"
      << "\\textbf{\\large Time: " << Date << "} \\\\* [0.3cm] \n";
   if (!BoxedText.empty()) {
      os << "\\textbox{0.5cm}{\\noindent " << BoxedText << " }\n";
   }
}

std::ostream &GenHeader::write(std::ostream &os, int level) const
{
   IGenerator::write(os, level);
   os << ": " << School << " ... " << Date << "\n";
   return os;
}
