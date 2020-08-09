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

IGenerator::IGenerator(std::string_view id)
   : ranges_{}
   , RSelectors_{}
   , type_{__func__}
   , id_{id}
   , level_{0}
{
}

IGenerator::~IGenerator()
{
   LOGD(type_ + ": '" + id_ + "'", 1);
}

std::ostream &IGenerator::write(std::ostream &os, int level) const
{
   LOGD(type_ + ": '" + id_ + "', level = " + std::to_string(level), 3);

   const std::string INDENTATION(level * 2, ' ');
   os << INDENTATION << type_ << " '" << id_ << "' " << this;

   return os;
}

void IGenerator::setID(std::string_view id)
{
   id_ = id;

   LOGD(type_ + ": updated id_ = '" + id_ + "'", 3);
}

void IGenerator::setLevel(int level)
{
   level_ = level;
}
