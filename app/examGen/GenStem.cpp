#include "GenStem.h"
#include "GenAPI.h"
#include "GenCodeText.h"
#include "GenText.h"
#include "Log.h"

#include <algorithm>
#include <string>

GenStem::GenStem(std::string_view id)
   : ICompositeGenerator{id}
   , index_{0}
{
   type_ = __func__;

   LOGD("'" + id_ + "' initialised", 2);
}

IGenPtr_t GenStem::copy() const
{
   std::shared_ptr<GenStem> p(new GenStem(*this));
   for_each(p->generators_.begin(), p->generators_.end(),
            [](IGenPtr_t &pGen) { pGen = pGen->copy(); });
   return p;
}

void GenStem::add(IGenPtr_t pGen)
{
   LOGD(type_ + ": '" + id_ + "', wants to add " + pGen->getType() + " " +
        pGen->getID(), 3);

   auto *p = pGen.get();
   if (GenText *pText = dynamic_cast<GenText *>(p)) {
      generators_.push_back(pGen);
   } else {
      if (GenCodeText *pCodeText = dynamic_cast<GenCodeText *>(p)) {
         generators_.push_back(pGen);
      } else {
         if (GenAPI *pAPI = dynamic_cast<GenAPI *>(p)) {
            generators_.push_back(pGen);
         } else {
            LOGE(type_ + ": '" + id_ + "', " + pGen->getID() +
                 " not allowed for adding");
         }
      }
   }
}

void GenStem::generate(std::ostream &os)
{
   LOGD(type_ + ": '" + id_ + "'", 3);

   for (auto &gen : generators_) {
      if (gen == nullptr) {
         LOGE(id_ + ", gen == nullptr");
      } else {
         gen->generate(os);
      }
   }
}

std::ostream &GenStem::write(std::ostream &os, int level) const
{
   ICompositeGenerator::write(os, level + 1);
   return os;
}

void GenStem::add(int index)
{
   index_ = index;
}
