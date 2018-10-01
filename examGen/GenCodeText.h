#ifndef GENCODETEXT_H
#define GENCODETEXT_H

#include <string>

#include "IGenerator.h"

class GenCodeText : public IGenerator
{
public:
   GenCodeText(const std::string &programmingLanguage,
               const std::string &codeText);
   virtual ~GenCodeText() = default;

   virtual IGenPtr_t copy() const override;
   virtual void generate(std::ostream &os) override;
   virtual std::ostream &write(std::ostream &os, int level = 0) const override;

private:
   const std::string programmingLanguage_;
   std::string codeText_;
};

#endif
