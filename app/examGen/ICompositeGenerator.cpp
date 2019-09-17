#include "ICompositeGenerator.h"
#include "Log.h"

ICompositeGenerator::ICompositeGenerator()
   : ICompositeGenerator{"NOT-DEFINED"}
{
}

ICompositeGenerator::ICompositeGenerator(const std::string &id)
   : IGenerator{id}
   , generators_{}
{
}

void ICompositeGenerator::generate(std::ostream &os)
{
   LOGD(type_ + ": " + id_);

   for (auto &gnrt : generators_) {
      LOGCW(gnrt == nullptr, type_ + ": " + id_ + ", missing generator");
      if (gnrt != nullptr) {
         gnrt->prepare();
         gnrt->generate(os);
      }
   }
}

std::ostream &ICompositeGenerator::write(std::ostream &os, int level) const
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
