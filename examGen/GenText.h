#ifndef GENTEXT_H
#define GENTEXT_H

#include "IGenerator.h"

#include <string>
class GenText : public IGenerator
{
public:
   GenText(const std::string& id, const std::string &text);
   virtual ~GenText() = default;

   IGenPtr_t copy() const override;
   void generate(std::ostream &os) override;
   std::ostream &write(std::ostream &os, int level = 0) const override;

private:
   std::string text_;
};

#endif
