#include <algorithm>
#include <boost/pointer_cast.hpp>
#include <string>

#include "ExcInfo.h"
#include "GenOption.h"
#include "GenOptions.h"
#include "Log.h"

using namespace std;

static bool lessLength(IGenPtr_t i1, IGenPtr_t i2)
{
   size_t s1 = (static_pointer_cast<GenOption>(i1))->size();
   size_t s2 = (static_pointer_cast<GenOption>(i2))->size();
   return s1 < s2;
}

GenOptions::GenOptions()
   : GenComposite()
   , preProcessing_{}
   , postProcessing_{}
{
   type_ = "GenOptions";
   LOGD("initialised");
}

GenOptions::~GenOptions()
{
   // IGenerator::write(clog) << " ##### DTOR" << endl;
}

IGenPtr_t GenOptions::copy() const
{
   std::shared_ptr<GenOptions> p(new GenOptions(*this));
   for_each(p->generators_.begin(), p->generators_.end(),
            [](IGenPtr_t &pGen) { pGen = pGen->copy(); });
   return p;
}

void GenOptions::add(IGenPtr_t pGen)
{
   try {
      if (std::shared_ptr<GenOption> pOption =
             std::dynamic_pointer_cast<GenOption>(pGen)) {
         generators_.push_back(pGen);
      } else {
         throw std::runtime_error(
            __AT__ "GenOptions: added type not allowed for adding");
      }
   }
   catch (exception &X) {
      clog << X.what() << endl;
   }
}

void GenOptions::generate(std::ostream &os)
{
   if (!preProcessing_.empty()) {
      os << preProcessing_ << "\n";
   }
   // Generate options
   os << "\n\\begin{enumerate}[label=\\Alph*.]\n";
   for (size_t i = 0; i < generators_.size(); ++i) {
      os << "\\item\n";
      generators_[i]->generate(os);
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
   random_shuffle(GenComposite::getGenerators().begin(),
                  GenComposite::getGenerators().end(), R);
}

void GenOptions::sort()
{
   stable_sort(GenComposite::getGenerators().begin(),
               GenComposite::getGenerators().end(), lessLength);
}
