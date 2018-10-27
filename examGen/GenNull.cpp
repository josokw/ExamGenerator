#include "GenNull.h"
#include "Log.h"

GenNull::GenNull()
   : ILeafGenerator{}
{
   type_ = "GenNull";

   LOGD(id_ + " initialised");
}

IGenPtr_t GenNull::copy() const
{
   std::shared_ptr<GenNull> p(new GenNull);
   return p;
}

void GenNull::generate(std::ostream &os)
{
   os << "$<$GenNUll$>$";
}

std::ostream &GenNull::write(std::ostream &os, int level) const
{
   return ILeafGenerator::write(os, level) << "\n";
}
