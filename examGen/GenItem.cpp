#include "GenItem.h"
#include "ExcInfo.h"
#include "GenAPI.h"
#include "GenCodeText.h"
#include "GenOption.h"
#include "GenOptions.h"
#include "GenStem.h"
#include "GenText.h"
#include "IGenerator.h"
#include "Log.h"

#include <algorithm>
#include <iterator>
#include <string>
#include <typeinfo>

// static bool lessLength(IGenPtr_t& i1, IGenPtr_t& i2)
//{
//  size_t s1 = (std::static_pointer_cast<GenOption>(i1))->size();
//  size_t s2 = (std::static_pointer_cast<GenOption>(i2))->size();
//  return s1 < s2;
//}

GenItem::GenItem()
   : GenItem{"NOT-DEFINED"}
{
}

GenItem::GenItem(const std::string &id)
   : GenComposite(id)
   , index_(0)
   , isLastItem_(false)
   , level_(0)
   , shuffleON_(false)
{
   type_ = "GenItem";
   generators_.push_back(std::shared_ptr<GenStem>(new GenStem()));
   generators_.push_back(std::shared_ptr<GenOptions>(new GenOptions()));

   LOGD(id_ + ", initialised");
}

IGenPtr_t GenItem::copy() const
{
   LOGD(type_ + ": " + id_);

   std::shared_ptr<GenItem> p(new GenItem(*this));
   for_each(p->generators_.begin(), p->generators_.end(),
            [](IGenPtr_t &pGen) { pGen = pGen->copy(); });
   return p;
}

void GenItem::add(IGenPtr_t pGen)
{
   LOGD(type_ + ": " + id_);
   try {
      if (std::shared_ptr<GenStem> pStem =
             std::dynamic_pointer_cast<GenStem>(pGen)) {
         generators_.push_back(pGen);
      } else {
         if (std::shared_ptr<GenOption> pOption =
                std::dynamic_pointer_cast<GenOption>(pGen)) {
            generators_.push_back(pGen);
         } else {
            if (std::shared_ptr<GenOptions> pOptions =
                   std::dynamic_pointer_cast<GenOptions>(pGen)) {
               generators_.push_back(pGen);
            } else {
               if (std::shared_ptr<GenAPI> pAPI =
                      std::dynamic_pointer_cast<GenAPI>(pGen)) {
                  generators_.push_back(pGen);
               }

               else {
                  throw std::runtime_error(__AT__ "GenItem: type '" +
                                           std::string(typeid(pGen).name()) +
                                           "' not allowed for adding");
               }
            }
         }
      }
   }
   catch (std::runtime_error &X) {
      std::cerr << X.what() << std::endl;
   }
}

void GenItem::generate(std::ostream &os)
{
   LOGD(type_ + ": " + id_);

   prepare();

   os << "\n% Item '" << getID() << "' generation: stem + options";
   if (isLastItem_) {
      os << " (last item)";
   }
   os << "\n";
   if (index_ == 1) {
      os << "% First item\n\\begin{enumerate}[label=\\arabic*.]\n";
   }

   // Generate stem
   os << "\\filbreak\n\\item\n";
   if (generators_[0] == nullptr) {
      LOGE(type_ + ": " + id_ + ", generators[0] == nullptr");
   } else {
      generators_[0]->generate(os);
   }

   // Generate options
   if (generators_[1] == nullptr) {
      LOGE(type_ + ": " + id_ + ", generators[1] == nullptr");
   } else {
      generators_[1]->generate(os);
   }
   os << "\\filbreak\n";

   if (isLastItem_) {
      os << "\n% Closing last item\n\\end{enumerate}\n";
   }
}

void GenItem::setIndex(int index)
{
   LOGD(type_ + ": " + id_ + ", index = " + std::to_string(index));
   index_ = index;
}

void GenItem::addToStem(IGenPtr_t pGen)
{
   LOGD(type_ + ": " + id_ + ", to add " + pGen->getID());

   try {
      IGenerator *p = pGen.get();
      if (dynamic_cast<GenText *>(p)) {
         generators_[0]->add(pGen);
      } else {
         if (dynamic_cast<GenCodeText *>(p)) {
            generators_[0]->add(pGen);
         } else {
            if (dynamic_cast<GenAPI *>(p)) {
               generators_[0]->add(pGen);
            } else {
               throw std::runtime_error(__AT__ "GenItem: type '" +
                                        std::string(typeid(pGen).name()) +
                                        "' not allowed for adding to stem");
            }
         }
      }
   }
   catch (std::runtime_error &e) {
      std::cerr << e.what() << std::endl;
   }
}

void GenItem::setAsLastItem() const
{
   LOGD(type_ + ": " + id_);

   isLastItem_ = true;
}

void GenItem::addToOptions(std::shared_ptr<GenOption> pOption, bool isCorrect)
{
   LOGD(type_ + ": " + id_);

   if (isCorrect) {
      pOption->setIsCorrect();
   }
   generators_[1]->add(IGenPtr_t(pOption));
}

void GenItem::setPreProOptions(const std::string &preProcessing)
{
   LOGD(id_);
   std::shared_ptr<GenOptions> pOptions =
      std::static_pointer_cast<GenOptions>(generators_[1]);
   pOptions->setPreProcessing(preProcessing);
}

void GenItem::setPostProOptions(const std::string &postProcessing)
{
   LOGD(id_);
   std::shared_ptr<GenOptions> pOptions =
      std::static_pointer_cast<GenOptions>(generators_[1]);
   pOptions->setPostProcessing(postProcessing);
}

void GenItem::setLevel(int level)
{
   LOGD(id_);

   level_ = level;
}

void GenItem::shuffleON()
{
   LOGD(id_);

   shuffleON_ = true;
}

void GenItem::sortOptions()
{
   LOGD(id_);

   std::shared_ptr<GenOptions> pOptions =
      std::static_pointer_cast<GenOptions>(generators_[1]);
   pOptions->sort();
}

std::ostream &GenItem::write(std::ostream &os, int level) const
{
   LOGD(id_);

   IGenerator::write(os, level);
   os << ": index = " << index_ << "\n";
   GenComposite::write(os, level + 1);
   os << "\n";

   return os;
}

void GenItem::prepare()
{
   if (shuffleON_) {
      std::shared_ptr<GenOptions> pOptions =
         std::static_pointer_cast<GenOptions>(generators_[1]);
      pOptions->shuffle();
   }
}
