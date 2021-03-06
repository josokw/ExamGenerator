#include "GenItem.h"
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

GenItem::GenItem(std::string_view id)
   : ICompositeGenerator{id}
   , index_{0}
   , isLastItem_{false}
   , level_{0}
   , shuffleON_{false}
{
   type_ = "GenItem";
   generators_.push_back(std::make_shared<GenStem>(id_ + ".stem"));
   generators_.push_back(std::make_shared<GenOptions>(id_ + ".options"));

   LOGD("'" + id_ + "', initialised", 2);
}

IGenPtr_t GenItem::copy() const
{
   LOGD(type_ + ": '" + id_ + "'", 3);

   auto p = std::make_shared<GenItem>(*this);
   for_each(p->generators_.begin(), p->generators_.end(),
            [](IGenPtr_t &pGen) { pGen = pGen->copy(); });
   return p;
}

void GenItem::add(IGenPtr_t pGen)
{
   LOGD(type_ + ": '" + id_ + "', wants to add " + pGen->getType() + " " +
           pGen->getID(),
        3);

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
            } else {
               LOGE("'" + id_ + "', " + pGen->getType() +
                    " not allowed for adding");
            }
         }
      }
   }
}

void GenItem::generate(std::ostream &os)
{
   LOGD(type_ + ": " + id_, 3);

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
   LOGD(type_ + ": '" + id_ + "', index = " + std::to_string(index), 3);

   index_ = index;
}

void GenItem::addToStem(IGenPtr_t pGen)
{
   LOGD(type_ + ": '" + id_ + "', to add " + pGen->getType() + " '" +
           pGen->getID() + "'",
        3);

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
            LOGE(type_ + ": '" + id_ + "', '" + pGen->getID() +
                 "' not allowed for adding to a stem");
         }
      }
   }
}

void GenItem::setAsLastItem() const
{
   LOGD(type_ + ": '" + id_ + "'", 3);

   isLastItem_ = true;
}

void GenItem::addToOptions(std::shared_ptr<GenOption> pOption, bool isCorrect)
{
   LOGD(type_ + ": '" + id_ + "', wants to add " + pOption->getType() + " '" +
           pOption->getID() + "'",
        3);

   if (isCorrect) {
      pOption->setIsCorrect();
      LOGD(type_ + ": '" + id_ + "': '" + pOption->getID() + "' is set correct",
           3);
   }
   generators_[1]->add(IGenPtr_t(pOption));
}

void GenItem::setPreProOptions(std::string_view preProcessing)
{
   LOGD(type_ + ": '" + id_ + "'", 3);

   std::shared_ptr<GenOptions> pOptions =
      std::static_pointer_cast<GenOptions>(generators_[1]);
   pOptions->setPreProcessing(preProcessing);
}

void GenItem::setPostProOptions(std::string_view postProcessing)
{
   LOGD(type_ + ": '" + id_ + "'", 3);

   std::shared_ptr<GenOptions> pOptions =
      std::static_pointer_cast<GenOptions>(generators_[1]);
   pOptions->setPostProcessing(postProcessing);
}

void GenItem::setLevel(int level)
{
   LOGD(type_ + ": '" + id_ + "'", 3);

   level_ = level;
}

void GenItem::shuffleON()
{
   LOGD(type_ + ": '" + id_ + "'", 3);

   shuffleON_ = true;
}

void GenItem::sortOptions()
{
   LOGD(type_ + ": '" + id_ + "'", 3);

   std::shared_ptr<GenOptions> pOptions =
      std::static_pointer_cast<GenOptions>(generators_[1]);
   pOptions->sort();
}

std::ostream &GenItem::write(std::ostream &os, int level) const
{
   LOGD(type_ + ": '" + id_ + "'", 3);

   IGenerator::write(os, level);
   os << ": index = " << index_ << "\n";
   ICompositeGenerator::write(os, level + 1);
   os << "\n";

   return os;
}

void GenItem::prepare()
{
   LOGD(type_ + ": '" + id_ + "'", 3);

   if (shuffleON_) {
      std::shared_ptr<GenOptions> pOptions =
         std::static_pointer_cast<GenOptions>(generators_[1]);
      pOptions->shuffle();
   }
}
