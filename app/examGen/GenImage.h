#ifndef GENIMAGE_H
#define GENIMAGE_H

#include "ILeafGenerator.h"

#include <string>

class GenImage : public ILeafGenerator
{
public:
   GenImage(std::string_view id, std::string_view fileName);
   ~GenImage() override = default;

   [[nodiscard]] IGenPtr_t copy() const override;
   void generate(std::ostream &os) override;
   std::ostream &write(std::ostream &os, int level = 0) const override;

private:
   std::string fileName_;
   std::string caption_;
};

#endif
