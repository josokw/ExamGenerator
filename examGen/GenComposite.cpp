#include <algorithm>
#include <iterator>
#include <string>

#include "GenComposite.h"
#include "Log.h"

GenComposite::GenComposite()
   : IGenerator()
   , generators_{}
{
   type_ = "GenComposite";
   LOGD("initialised");
}

GenComposite::GenComposite(const std::string &id)
   : IGenerator{id}
   , generators_{}
{
   type_ = "GenComposite";
   LOGD("initialised");
}

GenComposite::~GenComposite()
{
   // IGenerator::write(clog) << " ##### DTOR COMPOSITE" << endl;
}

void GenComposite::add(IGenPtr_t pGen)
{
   generators_.push_back(pGen);
}

std::ostream &GenComposite::write(std::ostream &os, int level) const
{
   IGenerator::write(os, level);
   os << "\n";
   for (auto &gen : generators_) {
      gen->write(os, level + 1);
   }
   //    for_each(generators_.begin(), generators_.end(),
   //             [&os, &level](IGenPtr_t g) { g->write(os, level + 1); });
   return os;
}

void GenComposite::generate(std::ostream &os)
{
   for (auto &gen : generators_) {
      gen->prepare();
      gen->generate(os);
   }
   //    for_each(generators_.begin(), generators_.end(), [&os](IGenPtr_t g) {
   //       g->prepare();
   //       g->generate(os);
   //    });
}
