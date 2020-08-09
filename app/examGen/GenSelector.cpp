#include "GenSelector.h"
#include "Log.h"

#include <algorithm>
#include <iterator>
#include <string>

GenSelector::GenSelector()
   : GenSelector{"NOT-DEFINED"}
{
}

GenSelector::GenSelector(std::string_view id)
   : ICompositeGenerator{id}
{
   type_ = __func__;

   LOGD("'" + id_ + "', initialised", 2);
}

IGenPtr_t GenSelector::copy() const
{
   std::shared_ptr<GenSelector> p(new GenSelector(*this));
   for_each(p->generators_.begin(), p->generators_.end(),
            [](IGenPtr_t &pGen) { pGen = pGen->copy(); });
   return p;
}

void GenSelector::add(IGenPtr_t pGen)
{
   LOGD(type_ + ": '" + id_ + "', wants to add " + pGen->getType() + " " +
        pGen->getID(), 3);

   allGenerators_.push_back(pGen);
   // for calculation a next permutation
   std::sort(begin(allGenerators_), end(allGenerators_));
}

void GenSelector::selectR(unsigned int n)
{
   LOGD(type_ + ": '" + id_ + "', n = " + std::to_string(n), 3);

   next_permutation(begin(allGenerators_), end(allGenerators_));
   generators_.clear();
   for (size_t i = 0; i < allGenerators_.size() && i < n; ++i) {
      generators_.push_back(allGenerators_[i]->copy());
   }
}

std::ostream &GenSelector::write(std::ostream &os, int level) const
{
   auto size = generators_.size();
   auto sizeAll = allGenerators_.size();

   IGenerator::write(os, level);
   os << ": size ALL = " << sizeAll << " size selected = " << size << "\n";
   return ICompositeGenerator::write(os, level + 1);
}
