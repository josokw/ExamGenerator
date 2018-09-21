#ifndef GENHEADER_H
#define GENHEADER_H

#include <string>

#include "IGenerator.h"

/// Represents a header of a MC exam document.
/// Every MC exam must have its own header.
/// Class invariant: TRUE
class GenHeader : public IGenerator
{
public:
   GenHeader();
   GenHeader(const std::string &id);
   virtual ~GenHeader();

   virtual IGenPtr_t copy() const;
   virtual void generate(std::ostream &os);
   virtual std::ostream &write(std::ostream &os, int level = 0) const;

   std::string School;
   std::string Course;
   std::string Lecturer;
   std::string Date;
   std::string BoxedText;
};

#endif
