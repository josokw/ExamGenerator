#include "GenSelector.h"
#include "Log.h"

#include <algorithm>
#include <iterator>
#include <string>

GenSelector::GenSelector()
   : GenComposite()
{
   type_ = "GenSelector";
   LOGD(id_ + " initialised");
}

GenSelector::GenSelector(const std::string &id)
   : GenComposite(id)
{
   type_ = "GenSelector";
   LOGD(id_ + " initialised");
}

GenSelector::~GenSelector()
{
   // IGenerator::write(clog) << " ##### DTOR" << endl;
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
   allGenerators_.push_back(pGen);
   // for calculation a next permutation
   std::sort(allGenerators_.begin(), allGenerators_.end());
}

void GenSelector::selectR(unsigned int n)
{
   next_permutation(allGenerators_.begin(), allGenerators_.end());
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
   return GenComposite::write(os, level + 1);
}
