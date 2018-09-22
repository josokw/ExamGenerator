#include "GenImage.h"
#include "Log.h"

#include <string>

GenImage::GenImage(const std::string &fileName)
   : fileName_{fileName}
   , caption_{}
{
   type_ = "Image";
   LOGD("initialised");
}

GenImage::~GenImage()
{
   // IGenerator::write(clog) << " ##### DTOR" << endl;
}

IGenPtr_t GenImage::copy() const
{
   std::shared_ptr<GenImage> p(new GenImage(fileName_));
   return p;
}

void GenImage::generate(std::ostream &os)
{
   os << "\n\\begin{figure}[h]\n\\begin{center} "
         "\\includegraphics[height=50mm]{"
      << fileName_ << "}\n\\end{center} \\end{figure}\n";
}

std::ostream &GenImage::write(std::ostream &os, int level) const
{
   IGenerator::write(os, level);
   os << ": " << fileName_ << "\n";

   return os;
}