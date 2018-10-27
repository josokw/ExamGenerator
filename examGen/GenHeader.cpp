#include "GenHeader.h"
#include "Log.h"

#include <string>

GenHeader::GenHeader()
   : GenHeader{"NOT-DEFINED"}
{
}

GenHeader::GenHeader(const std::string &id)
   : ILeafGenerator{id}
   , School{}
   , Course{}
   , Lecturer{}
   , Other{}
   , BoxedText{}
{
   type_ = "GenHeader";

   LOGD(id_ + ", initialised");
}

IGenPtr_t GenHeader::copy() const
{
   std::shared_ptr<GenHeader> p(new GenHeader(*this));
   return p;
}

void GenHeader::generate(std::ostream &os)
{
   LOGD(type_ + ": " + id_);

   os << "\\noindent\n";
   if (not School.empty()) {
      os << "\\textbf{\\LARGE " << School << "} \\newline \n";
   }
   if (not Course.empty()) {
      os << "\\textbf{\\large Course: " << Course << "} \\\\* \n";
   }
   if (not Lecturer.empty()) {
      os << "\\textbf{\\large Lecturer(s): " << Lecturer << "} \\\\* \n";
   }
   if (not Other.empty()) {
      os << "\\textbf{\\large " << Other << "} \\\\* \n";
   }
   os << " [0.3 cm] \n";
   if (not BoxedText.empty()) {
      os << "\\textbox{0.5cm}{\\noindent " << BoxedText << " }\n";
   }
}

std::ostream &GenHeader::write(std::ostream &os, int level) const
{
   IGenerator::write(os, level);
   os << ": " << School << " ... " << Other << "\n";
   return os;
}
