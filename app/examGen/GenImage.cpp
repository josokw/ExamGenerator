#include "GenImage.h"
#include "Log.h"

#include <string>

GenImage::GenImage(const std::string &id, const std::string &fileName)
   : ILeafGenerator{id}
   , fileName_{fileName}
   , caption_{}
{
   type_ = "GenImage";

   LOGD("'" + id_ + "', initialised", 2);
}

IGenPtr_t GenImage::copy() const
{
   LOGD(type_ + ": '" + id_ + "'", 3);

   std::shared_ptr<GenImage> p(new GenImage(id_, fileName_));
   return p;
}

void GenImage::generate(std::ostream &os)
{
   LOGD(type_ + ": '" + id_ + "'", 3);

   os << "\n\\begin{figure}[h]\n\\begin{center} "
         "\\includegraphics[height=50mm]{"
      << fileName_ << "}\n\\end{center} \\end{figure}\n";
}

std::ostream &GenImage::write(std::ostream &os, int level) const
{
   ILeafGenerator::write(os, level);
   os << ": " << fileName_ << "\n";

   return os;
}
