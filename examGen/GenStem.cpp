#include <string>

#include "ExcInfo.h"
#include "GenAPI.h"
#include "GenCodeText.h"
#include "GenStem.h"
#include "GenText.h"
#include "Log.h"

GenStem::GenStem()
   : GenComposite()
   , index_{0}
{
   type_ = "GenStem";
   LOGD(id_ + " initialised");
}

GenStem::~GenStem()
{
   LOGD(id_);
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
   try {
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
               LOGE(id_ + ", " + pGen->getType() +
                    " generator type not allowed for adding");
               throw std::runtime_error(__AT__ "Type not allowed for adding");
            }
         }
      }
   }
   catch (std::exception &X) {
      std::cerr << X.what() << std::endl;
   }
}

void GenStem::generate(std::ostream &os)
{
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
   GenComposite::write(os, level + 1);
   return os;
}

void GenStem::add(int index)
{
   index_ = index;
}
