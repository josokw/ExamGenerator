#ifndef ILEAFGENERATOR_H
#define ILEAFGENERATOR_H

#include "IGenerator.h"

#include <string>

/// Abstract base class for leaf generators.
/// @todo make class non-copyable
class ILeafGenerator : public IGenerator
{
public:
   ILeafGenerator();
   explicit ILeafGenerator(std::string_view id);
   ~ILeafGenerator() override = default;
   //    ILeafGenerator(const ILeafGenerator &other) = delete;
   ILeafGenerator &operator=(ILeafGenerator &other) = delete;

private:
   void add(IGenPtr_t pIGen) final;
};

#endif
