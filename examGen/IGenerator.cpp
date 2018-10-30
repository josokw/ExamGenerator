#include <iostream>
#include <string>

#include "IGenerator.h"
#include "Log.h"

std::ostream &operator<<(std::ostream &os, const IGenerator &iGen)
{
   return iGen.write(os);
}

RandomProfile IGenerator::randomProfile_s;

IGenerator::IGenerator()
   : IGenerator("NOT-DEFINED")
{
}

IGenerator::IGenerator(const std::string &id)
   : ranges_{}
   , RSelectors_{}
   , type_{"IGenerator"}
   , id_{id}
   , level_{0}
{
   LOGD(type_ + ": " + id_ + ", initialised");
}

IGenerator::~IGenerator()
{
   LOGD(type_ + ": " + id_);
}

std::ostream &IGenerator::write(std::ostream &os, int level) const
{
   LOGD(type_ + ": " + id_ + ", level = " + std::to_string(level));

   const std::string INDENTATION(level * 2, ' ');
   os << INDENTATION << type_ << " '" << id_ << "' " << this;

   return os;
}

void IGenerator::setID(const std::string &id)
{
   id_ = id;

   LOGD(type_ + ": id_ updated = " + id_);
}

void IGenerator::setLevel(int level)
{
   level_ = level;
}
