#include "GenNull.h"
#include "Log.h"

GenNull::GenNull()
   : IGenerator{}
{
   type_ = "GenNull";

   LOGD(id_ + " initialised");
}

IGenPtr_t GenNull::copy() const
{
   std::shared_ptr<GenNull> p(new GenNull(*this));
   return p;
}

void GenNull::generate(std::ostream &os)
{
   os << "$<$GenNUll$>$";
}

std::ostream &GenNull::write(std::ostream &os, int level) const
{
   return IGenerator::write(os, level) << "\n";
}
