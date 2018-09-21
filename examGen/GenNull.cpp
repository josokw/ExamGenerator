#include "GenNull.h"

GenNull::GenNull()
   : IGenerator()
{
   type_ = "GenNull";
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
   IGenerator::write(os, level);
   os << "\n";
   return os;
}
