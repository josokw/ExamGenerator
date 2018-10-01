#ifndef GENIMAGE_H
#define GENIMAGE_H

#include "IGenerator.h"

#include <string>

class GenImage : public IGenerator
{
public:
   GenImage(const std::string &fileName);
   virtual ~GenImage() = default;

   virtual IGenPtr_t copy() const override;
   virtual void generate(std::ostream &os) override;
   virtual std::ostream &write(std::ostream &os, int level = 0) const override;

private:
   std::string fileName_;
   std::string caption_;
};

#endif
