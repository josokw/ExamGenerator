#ifndef GENCODETEXT_H
#define GENCODETEXT_H

#include <string>

#include "ILeafGenerator.h"

class GenCodeText : public ILeafGenerator
{
public:
   GenCodeText(std::string_view id, std::string_view programmingLanguage,
               std::string_view codeText);
   ~GenCodeText() override = default;

   [[nodiscard]] IGenPtr_t copy() const override;
   void generate(std::ostream &os) override;
   std::ostream &write(std::ostream &os, int level = 0) const override;

private:
   const std::string programmingLanguage_;
   std::string codeText_;
};

#endif
