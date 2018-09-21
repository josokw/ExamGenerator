#ifndef GENTEXT_H
#define GENTEXT_H

#include <string>

#include "IGenerator.h"

class GenText : public IGenerator
{
public:
   GenText(const std::string &Text);
   virtual ~GenText();

   virtual IGenPtr_t copy() const;
   virtual void generate(std::ostream &os);
   virtual std::ostream &write(std::ostream &os, int Level = 0) const;

private:
   std::string text_;
};

#endif
