#include <sstream>
#include <vector>

#include "GenAPI.h"
#include "Log.h"

GenAPI::GenAPI(const std::string &returnType, const std::string &signature,
               const std::string &description)
   : IGenerator()
   , returnType_(returnType)
   , signature_(signature)
   , description_(description)
{
   type_ = "GenAPI";
   LOGD(id_ + ", initialised");
}

IGenPtr_t GenAPI::copy() const
{
   std::shared_ptr<GenAPI> p(new GenAPI(returnType_, signature_, description_));
   return p;
}

void GenAPI::generate(std::ostream &os)
{
   returnType_ = std::string(returnType_.begin() + 1, returnType_.end() - 1);
   signature_ = std::string(signature_.begin() + 1, signature_.end() - 1);
   description_ = std::string(description_.begin() + 1, description_.end() - 1);
   LOGD(id_ + ", " + returnType_ + " " + signature_);
   os << "\n\\vskip 0.4mm\n"
         "\\begin{tabular*}{0.8\\textwidth}{@{\\extracolsep{\\fill}} | r | "
         "p{4.0in} | } \n"
         "\\hline \n"
      << "\\textit{" << returnType_ << "} & \\textit{" << signature_
      << "}\n \\vskip 4 mm \\\\\n"
         " & \\textit{"
      << description_
      << "} \\\\\n"
         "\\hline \n"
         "\\end{tabular*}\n \\\\ \\\\\n";
}

std::ostream &GenAPI::write(std::ostream &os, int level) const
{
   IGenerator::write(os, level);
   os << ": " << returnType_ << " " << signature_ << "\n";
   return os;
}
