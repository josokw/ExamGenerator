#ifndef GENCODETEXT_H
#define GENCODETEXT_H

#include <string>

#include "ILeafGenerator.h"

class GenCodeText : public ILeafGenerator
{
public:
   GenCodeText(const std::string &id, const std::string &programmingLanguage,
               const std::string &codeText);
   virtual ~GenCodeText() = default;

   IGenPtr_t copy() const override;
   void generate(std::ostream &os) override;
   std::ostream &write(std::ostream &os, int level = 0) const override;

private:
   const std::string programmingLanguage_;
   std::string codeText_;
};

#endif
