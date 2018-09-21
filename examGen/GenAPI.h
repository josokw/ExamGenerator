#ifndef GENAPI_H
#define GENAPI_H

#include "IGenerator.h"

/// Generates an API description containing: return type, signature and
/// description.
class GenAPI : public IGenerator
{
public:
   GenAPI(const std::string &returnType, const std::string &signature,
          const std::string &description);
   virtual ~GenAPI();

   virtual IGenPtr_t copy() const;
   virtual void generate(std::ostream &os);
   virtual std::ostream &write(std::ostream &os, int level = 0) const;

private:
   std::string returnType_;
   std::string signature_;
   std::string description_;
};

#endif
