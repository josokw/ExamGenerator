#ifndef GENTEXT_H
#define GENTEXT_H

#include "IGenerator.h"

#include <string>
class GenText : public IGenerator
{
public:
   GenText(const std::string &Text);
   virtual ~GenText();

   virtual IGenPtr_t copy() const override;
   virtual void generate(std::ostream &os) override;
   virtual std::ostream &write(std::ostream &os, int Level = 0) const override;

private:
   std::string text_;
};

#endif
