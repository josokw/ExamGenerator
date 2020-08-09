#include "GenOptions.h"
#include "GenOption.h"
#include "GenRandom.h"
#include "Log.h"
#include "Seed.h"

#include <algorithm>
#include <random>
#include <string>

namespace {

bool lessLength(IGenPtr_t i1, IGenPtr_t i2)
{
   auto s1 = (std::static_pointer_cast<GenOption>(i1))->size();
   auto s2 = (std::static_pointer_cast<GenOption>(i2))->size();
   return s1 < s2;
}

} // namespace

GenRandom GenOptions::genrnd_s{getSeed() + 12345};

GenOptions::GenOptions(std::string_view id)
   : ICompositeGenerator{id}
   , preProcessing_{}
   , postProcessing_{}
{
   type_ = __func__;

   LOGD("'" + id_ + "' initialised, seed = " + std::to_string(seed), 2);
}

IGenPtr_t GenOptions::copy() const
{
   LOGD(type_ + ": '" + id_ + "'", 3);

   std::shared_ptr<GenOptions> p(new GenOptions(*this));
   for_each(p->generators_.begin(), p->generators_.end(),
            [](IGenPtr_t &pGen) { pGen = pGen->copy(); });
   return p;
}

void GenOptions::add(IGenPtr_t pGen)
{
   LOGD(type_ + ": '" + id_ + "', wants to add " + pGen->getType() + " '" +
           pGen->getID() + "'",
        3);

   if (std::shared_ptr<GenOption> pOption =
          std::dynamic_pointer_cast<GenOption>(pGen)) {
      generators_.push_back(pGen);
   } else {
      LOGE(type_ + ": '" + id_ + "', '" + pGen->getID() +
           "' not allowed for adding");
   }
}

void GenOptions::generate(std::ostream &os)
{
   LOGD(type_ + ": '" + id_ + "'", 3);

   if (!preProcessing_.empty()) {
      os << preProcessing_ << "\n";
   }
   // Generate options
   os << "\n\\begin{enumerate}[label=\\Alph*.]\n";
   for (auto &gen : generators_) {
      os << "\\item\n";
      if (gen != nullptr) {
         gen->generate(os);
      } else {
         LOGE(id_ + ", gen == nullptr");
      }
   }
   os << "\\end{enumerate}\n\\vskip 5mm\n";
   if (!postProcessing_.empty()) {
      os << postProcessing_ << "\n";
   }
}

std::ostream &GenOptions::write(std::ostream &os, int Level) const
{
   ICompositeGenerator::write(os, Level + 1);
   return os;
}

void GenOptions::add(std::shared_ptr<GenOption> &pOption, bool isCorrect)
{
   if (isCorrect) {
      pOption->setIsCorrect();
   }
   generators_.push_back(pOption);
}

void GenOptions::shuffle()
{
   LOGD(type_ + ": '" + id_ + "'", 3);

   auto rgen = [=](int i) { return genrnd_s.generate(i); };

   std::random_shuffle(begin(getGenerators()), end(getGenerators()), rgen);
}

void GenOptions::sort()
{
   LOGD(type_ + ": " + id_, 3);

   std::stable_sort(begin(getGenerators()), end(getGenerators()), lessLength);
}
