#ifndef GENTWOC_H
#define GENTWOC_H

#include "GenItem.h"

#include <list>
#include <tuple>

class GenTwoC : public GenItem
{
public:
   GenTwoC();
   virtual ~GenTwoC() = default;

protected:
   virtual void prepare() override;

private:
   static std::tuple<Random::range_t, int, std::list<int>, int> R0_s;
};

#endif