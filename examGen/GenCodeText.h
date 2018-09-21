#ifndef GENCODETEXT_H
#define GENCODETEXT_H

#include <string>

#include "IGenerator.h"

class GenCodeText : public IGenerator
{
public:
   GenCodeText(const std::string &programmingLanguage,
               const std::string &codeText);
   virtual ~GenCodeText();

   virtual IGenPtr_t copy() const;
   virtual void generate(std::ostream &os);
   virtual std::ostream &write(std::ostream &os, int level = 0) const;

private:
   const std::string programmingLanguage_;
   std::string codeText_;
};

#endif
