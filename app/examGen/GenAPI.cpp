#include "GenAPI.h"
#include "Log.h"

#include <sstream>
#include <vector>

GenAPI::GenAPI(std::string_view returnType, std::string_view signature,
               std::string_view description)
   : ILeafGenerator{}
   , returnType_{returnType}
   , signature_{signature}
   , description_{description}
{
   type_ = __func__;

   LOGD("'" + id_ + "', initialised", 2);
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

   LOGD(type_ + ": '" + id_ + "', " + returnType_ + " " + signature_, 3);

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
   ILeafGenerator::write(os, level);
   os << ": " << returnType_ << " " << signature_ << "\n";

   return os;
}
