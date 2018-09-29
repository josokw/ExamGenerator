#include <algorithm>
#include <boost/pointer_cast.hpp>
#include <string>

#include "ExcInfo.h"
#include "GenOption.h"
#include "GenOptions.h"
#include "Log.h"

namespace {

bool lessLength(IGenPtr_t i1, IGenPtr_t i2)
{
   auto s1 = (std::static_pointer_cast<GenOption>(i1))->size();
   auto s2 = (std::static_pointer_cast<GenOption>(i2))->size();
   return s1 < s2;
}

} // namespace

GenOptions::GenOptions()
   : GenComposite()
   , preProcessing_{}
   , postProcessing_{}
{
   type_ = "GenOptions";
   LOGD(id_ + " initialised");
}

GenOptions::~GenOptions()
{
   LOGD(id_);
}

IGenPtr_t GenOptions::copy() const
{
   LOGD(id_);
   std::shared_ptr<GenOptions> p(new GenOptions(*this));
   for_each(p->generators_.begin(), p->generators_.end(),
            [](IGenPtr_t &pGen) { pGen = pGen->copy(); });
   return p;
}

void GenOptions::add(IGenPtr_t pGen)
{
   LOGD(id_);
   try {
      if (std::shared_ptr<GenOption> pOption =
             std::dynamic_pointer_cast<GenOption>(pGen)) {
         generators_.push_back(pGen);
      } else {
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
   LOGD(id_);
   if (!preProcessing_.empty()) {
      os << preProcessing_ << "\n";
   }
   // Generate options
   os << "\n\\begin{enumerate}[label=\\Alph*.]\n";
   for (size_t i = 0; i < generators_.size(); ++i) {
      os << "\\item\n";
      if (generators_[i] != nullptr) {
         generators_[i]->generate(os);
      } else {
         LOGE(id_ + ", generators_[i] == nullptr");
      }
   }
   os << "\\end{enumerate}\n\\vskip 5mm\n";
   if (!postProcessing_.empty()) {
      os << postProcessing_ << "\n";
   }
}

std::ostream &GenOptions::write(std::ostream &os, int Level) const
{
   GenComposite::write(os, Level + 1);
   return os;
}

void GenOptions::add(std::shared_ptr<GenOption> &pOption, bool isCorrect)
{
   if (isCorrect) {
      pOption->setIsCorrect();
   }
   generators_.push_back(IGenPtr_t(pOption));
}

void GenOptions::shuffle()
{
   static Random R(10);

   //    for (auto &gen : GenComposite::getGenerators()) {
   //       std::cerr << gen->getID() << std::endl;
   //    }

   //    std::random_shuffle(GenComposite::getGenerators().begin(),
   //                        GenComposite::getGenerators().end(), R);

   std::random_shuffle(begin(GenComposite::getGenerators()),
                       end(GenComposite::getGenerators()));

   //    for (auto &gen : GenComposite::getGenerators()) {
   //       std::cerr << gen->getID() << std::endl;
   //    }
}

void GenOptions::sort()
{
   std::stable_sort(begin(GenComposite::getGenerators()),
                    end(GenComposite::getGenerators()), lessLength);
}
