#include "GenNull.h"

GenNULL::GenNULL()
   : IGenerator()
{
   type_ = "GENNULL";
}

IGenPtr_t GenNULL::copy() const
{
   std::shared_ptr<GenNULL> p(new GenNULL(*this));
   return p;
}

void GenNULL::generate(std::ostream &os)
{
   os << "$<$NULL$>$";
}

std::ostream &GenNULL::write(std::ostream &os, int level) const
{
   IGenerator::write(os, level);
   os << "\n";
   return os;
}
