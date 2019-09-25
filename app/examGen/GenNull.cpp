#include "GenNull.h"
#include "Log.h"

GenNull::GenNull()
   : ILeafGenerator{}
{
   type_ = __func__;

   LOGD(id_ + " initialised", 2);
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
