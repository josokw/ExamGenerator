#ifndef GENTEXT_H
#define GENTEXT_H

#include "ILeafGenerator.h"

#include <string>
class GenText : public ILeafGenerator
{
public:
   GenText(std::string_view id, std::string_view text);
   ~GenText() override = default;

   [[nodiscard]] IGenPtr_t copy() const override;
   void generate(std::ostream &os) override;
   std::ostream &write(std::ostream &os, int level = 0) const override;

private:
   std::string text_;
};

#endif
