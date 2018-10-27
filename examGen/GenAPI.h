#ifndef GENAPI_H
#define GENAPI_H

#include "ILeafGenerator.h"

/// Generates an API function description containing: return type, signature and
/// description.
class GenAPI : public ILeafGenerator
{
public:
   GenAPI(const std::string &returnType, const std::string &signature,
          const std::string &description);
   virtual ~GenAPI() = default;

   IGenPtr_t copy() const override;
   void generate(std::ostream &os) override;
   std::ostream &write(std::ostream &os, int level = 0) const override;

private:
   std::string returnType_;
   std::string signature_;
   std::string description_;
};

#endif
