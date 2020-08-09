#ifndef GENAPI_H
#define GENAPI_H

#include "ILeafGenerator.h"

/// Generates an API function description containing: return type, signature and
/// description.
class GenAPI : public ILeafGenerator
{
public:
   GenAPI(std::string_view returnType, std::string_view signature,
          std::string_view description);
   ~GenAPI() override = default;

   [[nodiscard]] IGenPtr_t copy() const override;
   void generate(std::ostream &os) override;
   std::ostream &write(std::ostream &os, int level = 0) const override;

private:
   std::string returnType_;
   std::string signature_;
   std::string description_;
};

#endif
