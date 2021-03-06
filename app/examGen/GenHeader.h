#ifndef GENHEADER_H
#define GENHEADER_H

#include "ILeafGenerator.h"

#include <string>

/// Represents a header of an exam document. Every exam must have its own
/// header.
///
/// Class invariant: TRUE
class GenHeader : public ILeafGenerator
{
public:
   GenHeader();
   GenHeader(std::string_view id);
   ~GenHeader() override = default;

   [[nodiscard]] IGenPtr_t copy() const override;
   void generate(std::ostream &os) override;
   std::ostream &write(std::ostream &os, int level = 0) const override;

   std::string School;
   std::string Course;
   std::string Lecturer;
   std::string Other;
   std::string BoxedText;
};

#endif
