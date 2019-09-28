#include "GenLogicFactory.h"
#include "GenHeader.h"
#include "GenLogicDiagramAON.h"
#include "GenLogicDiagramAOXN.h"
#include "GenTwoC.h"
#include "IGenerator.h"
#include "Log.h"

#include <iostream>

GenLogicFactory::GenLogicFactory()
{
   addGenerator(std::string("LogicDiagramAON"),
                std::make_shared<GenLogicDiagramAON>());
   addGenerator(std::string("LogicDiagramAOXN"),
                std::make_shared<GenLogicDiagramAOXN>());
   addGenerator(std::string("TwoC"), std::make_shared<GenTwoC>());
}

IGenPtr_t GenLogicFactory::create(const std::string &key) const
{
   LOGD("key = " + key, 3);
   auto gen = factory_.create(key);
   LOGCE(nullptr == gen, ", generator " + key + " not in factory");

   return gen;
}

void GenLogicFactory::addGenerator(const std::string &key, IGenPtr_t pGenerator)
{
   LOGD("key = " + key + " generator id = " + pGenerator->getID(), 3);
   
   if (factory_.keyIsAlreadyRegistered(key)) {
      LOGW("Generator '" + key + "' is not unique, already registered");
   }
   factory_.addToRegistry(key, pGenerator);
}
