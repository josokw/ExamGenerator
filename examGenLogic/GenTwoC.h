#ifndef GENTWOC_H
#define GENTWOC_H

#include "GenItem.h"

#include <list>
#include <tuple>

class GenTwoC final : public GenItem
{
public:
   GenTwoC();
   ~GenTwoC() override = default;

protected:
   void prepare() override;

private:
   static RandomProfile::fullR_t R0_s;
};

#endif