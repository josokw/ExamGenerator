#include "ILeafGenerator.h"
#include "Log.h"

ILeafGenerator::ILeafGenerator()
   : ILeafGenerator{"NOT-DEFINED"}
{
}

ILeafGenerator::ILeafGenerator(std::string_view id)
   : IGenerator{id}
{
}

void ILeafGenerator::add(IGenPtr_t pIGen)
{
   LOGE(type_ + ": '" + id_ + "', adding is not allowed");
}
