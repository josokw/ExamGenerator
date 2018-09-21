#include <string>

#include "ExcInfo.h"
#include "GenAPI.h"
#include "GenCodeText.h"
#include "GenStem.h"
#include "GenText.h"

using namespace std;

GenStem::GenStem()
   : GenComposite()
   , index_{0}
{
   type_ = "GenStem";
}

GenStem::~GenStem()
{
   // IGenerator::write(clog) << " ##### DTOR" << endl;
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
               throw runtime_error(__AT__ "Type not allowed for adding");
            }
         }
      }
   }
   catch (exception &X) {
      clog << X.what() << endl;
   }
}

void GenStem::generate(std::ostream &os)
{
   for_each(generators_.begin(), generators_.end(),
            [&os](IGenPtr_t &g) { g->generate(os); });
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
