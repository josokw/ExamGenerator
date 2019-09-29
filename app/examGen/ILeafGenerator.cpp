#include "ILeafGenerator.h"
#include "Log.h"

ILeafGenerator::ILeafGenerator()
   : ILeafGenerator{"NOT-DEFINED"}
{
}

ILeafGenerator::ILeafGenerator(const std::string &id)
   : IGenerator{id}
{
}

void ILeafGenerator::add(IGenPtr_t pIGen)
{
   LOGE(type_ + ": '" + id_ + "', adding is not allowed");
}
