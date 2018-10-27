#include "GenImage.h"
#include "Log.h"

#include <string>

GenImage::GenImage(const std::string &fileName)
   : ILeafGenerator{}
   , fileName_{fileName}
   , caption_{}
{
   type_ = "GenImage";

   LOGD(id_ + ", initialised");
}

IGenPtr_t GenImage::copy() const
{
   LOGD(type_ + ": " + id_);

   std::shared_ptr<GenImage> p(new GenImage(fileName_));
   return p;
}

void GenImage::generate(std::ostream &os)
{
   LOGD(type_ + ": " + id_);
   
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
