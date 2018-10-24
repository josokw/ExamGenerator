#include <algorithm>
#include <iterator>
#include <string>

#include "GenComposite.h"
#include "Log.h"

GenComposite::GenComposite()
   : GenComposite{"NOT-DEFINED"}
{
}

GenComposite::GenComposite(const std::string &id)
   : IGenerator{id}
   , generators_{}
{
   type_ = "GenComposite";
   LOGD(id_ + ", initialised");
}

void GenComposite::add(IGenPtr_t pGen)
{
   LOGD(type_ + ": " + id_ + ", want to add " + pGen->getType() + " " +
        pGen->getID());

   generators_.push_back(pGen);
}

std::ostream &GenComposite::write(std::ostream &os, int level) const
{
   os << "\n";
   for (auto &gen : generators_) {
      if (gen == nullptr) {
         LOGE(type_ + ": " + id_ + ", gen == nullptr");
      } else {
         gen->write(os, level + 1);
      }
   }

   return os;
}

void GenComposite::generate(std::ostream &os)
{
   LOGD(type_ + ": " + id_);

   for (auto &gen : generators_) {
      LOGCW(gen == nullptr, type_ + ": " + id_);
      if (gen != nullptr) {
         gen->prepare();
         gen->generate(os);
      }
   }
}

bool GenComposite::generatorsCheck() const
{
   bool isOk{true};
   for (auto &ptr : generators_) {
      if (ptr == nullptr) {
         isOk = false;
         break;
      }
   }

   LOGCW(!isOk, type_ + ": " + id_);
   return isOk;
}
