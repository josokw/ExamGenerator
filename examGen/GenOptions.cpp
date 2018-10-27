#include "GenOptions.h"
#include "ExcInfo.h"
#include "GenOption.h"
#include "Log.h"

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

GenOptions::GenOptions(const std::string &id)
   : ICompositeGenerator{id}
   , preProcessing_{}
   , postProcessing_{}
{
   type_ = "GenOptions";

   LOGD(id_ + " initialised");
}

IGenPtr_t GenOptions::copy() const
{
   LOGD(type_ + ": " + id_);

   std::shared_ptr<GenOptions> p(new GenOptions(*this));
   for_each(p->generators_.begin(), p->generators_.end(),
            [](IGenPtr_t &pGen) { pGen = pGen->copy(); });
   return p;
}

void GenOptions::add(IGenPtr_t pGen)
{
   LOGD(type_ + ": " + id_ + ", wants to add " + pGen->getType() + " " +
        pGen->getID());

   try {
      if (std::shared_ptr<GenOption> pOption =
             std::dynamic_pointer_cast<GenOption>(pGen)) {
         generators_.push_back(pGen);
      } else {
         LOGE(type_ + ": " + id_ + ", " + pGen->getID() +
              " not allowed for adding");
         throw std::runtime_error(
            __AT__ "GenOptions: added type not allowed for adding");
      }
   }
   catch (std::exception &X) {
      std::cerr << X.what() << std::endl;
   }
}

void GenOptions::generate(std::ostream &os)
{
   LOGD(type_ + ": " + id_);

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
   LOGD(type_ + ": " + id_);

   std::random_device rd;
   std::mt19937 g(rd());

   std::random_shuffle(begin(getGenerators()), end(getGenerators()));
}

void GenOptions::sort()
{
   LOGD(type_ + ": " + id_);

   std::stable_sort(begin(getGenerators()), end(getGenerators()), lessLength);
}
