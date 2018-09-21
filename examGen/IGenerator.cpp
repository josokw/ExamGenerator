#include <iostream>
#include <string>

#include "ExcInfo.h"
#include "IGenerator.h"
#include "Log.h"

std::ostream &operator<<(std::ostream &os, const IGenerator &iGen)
{
   return iGen.write(os);
}

RandomProfile IGenerator::randomProfile_s;

IGenerator::IGenerator()
   : ranges_()
   , RSelectors_()
   , type_("NOT-DEFINED")
   , id_("NOT-DEFINED")
   , difficultyLevel_(0)
{
     LOGD("initialised");
}

IGenerator::IGenerator(const std::string &id)
   : ranges_()
   , RSelectors_()
   , type_("NOT-DEFINED")
   , id_(id)
   , difficultyLevel_(0)
{
}

IGenerator::~IGenerator()
{
   // IGenerator::write(clog) << " ##### DTOR IGenerator" << endl;
}

void IGenerator::add(IGenPtr_t pGen)
{
   throw std::runtime_error( //__AT__
      "Leaf object type in composite: no adding allowed");
}

std::ostream &IGenerator::write(std::ostream &os, int level) const
{
   const std::string INDENTATION(level * 2, ' ');
   os << INDENTATION << type_ << " '" << id_ << "' " << this;
   return os;
}
