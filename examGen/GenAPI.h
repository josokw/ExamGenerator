#ifndef GENAPI_H
#define GENAPI_H

#include "IGenerator.h"

/// Generates an API function description containing: return type, signature and
/// description.
class GenAPI : public IGenerator
{
public:
   GenAPI(const std::string &returnType, const std::string &signature,
          const std::string &description);
   virtual ~GenAPI() = default;

   virtual IGenPtr_t copy() const override;
   virtual void generate(std::ostream &os) override;
   virtual std::ostream &write(std::ostream &os, int level = 0) const override;

private:
   std::string returnType_;
   std::string signature_;
   std::string description_;
};

#endif
