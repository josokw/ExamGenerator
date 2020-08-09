#include "GenCFactory.h"
#include "GenHeader.h"
#include "GenLogicExprAON.h"
#include "GenLogicExprAOXN.h"
#include "GenNestedFor.h"
#include "IGenerator.h"
#include "Log.h"

#include <iostream>

GenCFactory::GenCFactory()
{
   addGenerator(std::string("LogicExprAON"),
                std::make_shared<GenLogicExprAON>());
   addGenerator(std::string("LogicExprAOXN"),
                std::make_shared<GenLogicExprAOXN>());
   addGenerator(std::string("NestedFor"), std::make_shared<GenNestedFor>());
}

IGenPtr_t GenCFactory::create(const std::string &key) const
{
   LOGD("key = " + key, 3);
   auto gen = factory_.create(key);
   LOGCE(nullptr == gen, ", generator " + key + " not in factory");

   return gen;
}

void GenCFactory::addGenerator(const std::string &key, IGenPtr_t pGenerator)
{
   LOGD("key = " + key + " generator id = " + pGenerator->getID(),
        3);

   if (factory_.keyIsAlreadyRegistered(key)) {
      LOGW("Generator '" + key + "' is not unique, already registered");
   }
   factory_.addToRegistry(key, pGenerator);
}
