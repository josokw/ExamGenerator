#include "GenExam.h"
#include "ExcInfo.h"
#include "GenCodeText.h"
#include "GenHeader.h"
#include "GenImage.h"
#include "GenItem.h"
#include "GenOption.h"
#include "GenOptions.h"
#include "GenSelector.h"
#include "GenSolution.h"
#include "GenText.h"
#include "Log.h"

#include <memory>
#include <stdexcept>

int GenExam::nExams_s = 0;

GenExam::GenExam(std::vector<message_t> &messages)
   : GenComposite()
   , messages(messages)
   , HeaderIsAdded(false)
   , pLastAddedItem()
   , indexLastAddedItem(0)
   , pGenSolution()
{
   type_ = "GenExam";
   ++nExams_s;
}

GenExam::~GenExam()
{
   //  IGenerator::write(clog) << " ##### DTOR" << endl;
}

IGenPtr_t GenExam::copy() const
{
   std::shared_ptr<GenExam> p(new GenExam(*this));
   for_each(p->generators_.begin(), p->generators_.end(),
            [](IGenPtr_t &pGen) { pGen = pGen->copy(); });

   return p;
}

std::ostream &GenExam::write(std::ostream &os, int level) const
{
   IGenerator::write(os, level);
   os << ": size = " << generators_.size() << "\n";
   GenComposite::write(os, level + 1);
   os << "-------- END GenExam: '" << getID() << "'\n";

   return os;
}

void GenExam::add(IGenPtr_t pGen)
{
   try {
      if (std::shared_ptr<GenHeader> pHeader =
             std::dynamic_pointer_cast<GenHeader>(pGen)) {
         if (!HeaderIsAdded) {
            generators_.push_back(pGen);
            HeaderIsAdded = true;
         } else {
            messages.push_back(message_t('E', 0, 0,
                                                 "A header in MCT '" + getID() +
                                                    "' is already added"));
         }
      } else {
         if (std::shared_ptr<GenItem> pItem =
                std::dynamic_pointer_cast<GenItem>(pGen)) {
            if (!HeaderIsAdded) {
               messages.push_back(message_t(
                  'E', 0, 0, "A header in MCT '" + getID() + "' is missing"));
            }

            // Start counting number of correct options, should be >= 1.
            int nIsCorrect = 0;
            if (std::shared_ptr<GenOptions> pOptions =
                   std::dynamic_pointer_cast<GenOptions>((*pItem)[1])) {
               for (size_t i = 0; i < pOptions->size(); ++i) {
                  if (std::shared_ptr<GenOption> pOption =
                         std::dynamic_pointer_cast<GenOption>((*pOptions)[i])) {
                     if (pOption->getIsCorrect()) {
                        ++nIsCorrect;
                     }
                  }
               }
               pLastAddedItem = pItem;
               generators_.push_back(pLastAddedItem);
               ++indexLastAddedItem;
               pItem->setIndex(indexLastAddedItem);
               if (nIsCorrect == 0) {
                  messages.push_back(message_t(
                     'E', 0, 0,
                     "No option for item '" + pItem->getID() + "' is correct"));
               }
            } else {
               messages.push_back(message_t(
                  'E', 0, 0, "No GenOptions object available."));
            }
         } else {
            if (std::shared_ptr<GenOption> pOption =
                   std::dynamic_pointer_cast<GenOption>(pGen)) {
               generators_.push_back(pGen);
            } else {
               if (std::shared_ptr<GenText> pText =
                      std::dynamic_pointer_cast<GenText>(pGen)) {
                  generators_.push_back(pGen);
               } else {
                  if (std::shared_ptr<GenCodeText> pJava =
                         std::dynamic_pointer_cast<GenCodeText>(pGen)) {
                     generators_.push_back(pGen);
                  } else {
                     if (std::shared_ptr<GenImage> pImage =
                            std::dynamic_pointer_cast<GenImage>(pGen)) {
                        generators_.push_back(pGen);
                     } else {
                        if (std::shared_ptr<GenSelector> pSelector =
                               std::dynamic_pointer_cast<GenSelector>(pGen)) {
                           // Do not add a Selector object but add Selector
                           // contents
                           for (size_t i = 0; i < pSelector->size(); ++i) {
                              add((*pSelector)[i]);
                           }
                           // cout << *this << endl;
                        } else {
                           if (std::shared_ptr<GenSolution> pSol =
                                  std::dynamic_pointer_cast<GenSolution>(
                                     pGen)) {
                              if (indexLastAddedItem > 0) {
                                 generators_.push_back(pGen);
                              } else {
                                 throw std::domain_error(
                                    __AT__ "MCT " + getID() +
                                    " no items available for "
                                    "generating solution");
                              }
                           } else {
                              throw std::runtime_error(
                                 __AT__ "MCT " + getID() + " generator '" +
                                 pGen->getID() +
                                 "' type not allowed for adding");
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }
   catch (std::runtime_error &X) {
      std::clog << X.what() << std::endl;
   }
   catch (std::exception &X) {
      std::clog << X.what() << std::endl;
   }
}

void GenExam::setLastItem()
{
   pLastAddedItem->setAsLastItem();
}

void GenExam::generate(std::ostream &os)
{
   // GenItem::clearIndexCount();
   if (pLastAddedItem) {
      pLastAddedItem->setAsLastItem();
   }
   os << "% Start of MCT '" << getID() << "' generation\n";
   if (nExams_s > 1) {
      os << "\\newpage\n\\setcounter{page}{1}\n\n";
   }
   std::shared_ptr<GenSolution> pGenSol(new GenSolution(this));
   pGenSol->setID(getID() + ".solution");
   add(pGenSol);
   for_each(generators_.begin(), generators_.end(),
            [&os](std::shared_ptr<IGenerator> &gen) { gen->generate(os); });
   os << "\n% End of exam '" << getID() << "' generation\n\n";
}