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
   : GenComposite{}
   , messages_{messages}
   , headerIsAdded_{false}
   , pLastAddedItem_{nullptr}
   , indexLastAddedItem_{0}
   , pGenSolution_{nullptr}
{
   type_ = "GenExam";
   ++nExams_s;
   LOGD(id_ + ", initialised, nExams_s = " + std::to_string(nExams_s));
}

GenExam::~GenExam()
{
   --nExams_s;
   LOGD(id_ + ", nExams_s = " + std::to_string(nExams_s));
}

IGenPtr_t GenExam::copy() const
{
   LOGD(type_ + ": " + id_);
   std::shared_ptr<GenExam> p(new GenExam(*this));
   //    for (auto &gen : generators_) {
   //       gen = gen->copy();
   //    }
   for_each(p->generators_.begin(), p->generators_.end(),
            [this](IGenPtr_t &pGen) {
               if (pGen == nullptr) {
                  LOGW(type_ + ": " + id_ + ", pGen == nullptr");
               } else {
                  pGen = pGen->copy();
               }
            });

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
   LOGD(type_ + ": " + id_);

   try {
      if (auto pHeader = std::dynamic_pointer_cast<GenHeader>(pGen)) {
         if (!headerIsAdded_) {
            generators_.push_back(pGen);
            headerIsAdded_ = true;
         } else {
            LOGE(id_ + ", a header is already added");
            messages_.push_back(message_t(
               'E', 0, 0, "A header '" + getID() + "' is already added"));
         }
      } else {
         if (auto pItem = std::dynamic_pointer_cast<GenItem>(pGen)) {
            if (!headerIsAdded_) {
               LOGE(id_ + ", a header is missing");
               messages_.push_back(message_t(
                  'E', 0, 0, "A header '" + getID() + "' is missing"));
            }

            // Start counting number of correct options, should be >= 1.
            if (auto pOptions =
                   std::dynamic_pointer_cast<GenOptions>((*pItem)[1])) {
               int nIsCorrect = 0;
               for (size_t i = 0; i < pOptions->size(); ++i) {
                  if (auto pOption =
                         std::dynamic_pointer_cast<GenOption>((*pOptions)[i])) {
                     if (pOption->getIsCorrect()) {
                        ++nIsCorrect;
                     }
                  }
               }
               pLastAddedItem_ = pItem;
               generators_.push_back(pLastAddedItem_);
               ++indexLastAddedItem_;
               pItem->setIndex(indexLastAddedItem_);
               if (nIsCorrect == 0) {
                  LOGE(id_ + "No option for item '" + pItem->getID() +
                       "' is correct");
                  messages_.push_back(message_t(
                     'E', 0, 0,
                     "No option for item '" + pItem->getID() + "' is correct"));
               }
            } else {
               LOGE(id_ + ", no GenOptions object available");
               messages_.push_back(
                  message_t('E', 0, 0, "No GenOptions object available."));
            }
         } else {
            if (auto pOption = std::dynamic_pointer_cast<GenOption>(pGen)) {
               generators_.push_back(pGen);
            } else {
               if (auto pText = std::dynamic_pointer_cast<GenText>(pGen)) {
                  generators_.push_back(pGen);
               } else {
                  if (auto pCodeText =
                         std::dynamic_pointer_cast<GenCodeText>(pGen)) {
                     generators_.push_back(pGen);
                  } else {
                     if (auto pImage =
                            std::dynamic_pointer_cast<GenImage>(pGen)) {
                        generators_.push_back(pGen);
                     } else {
                        if (auto pSelector =
                               std::dynamic_pointer_cast<GenSelector>(pGen)) {
                           // Do not add a Selector object but add Selector
                           // contents
                           for (size_t i = 0; i < pSelector->size(); ++i) {
                              add((*pSelector)[i]);
                           }
                           // cout << *this << endl;
                        } else {
                           if (auto pSol =
                                  std::dynamic_pointer_cast<GenSolution>(
                                     pGen)) {
                              if (indexLastAddedItem_ > 0) {
                                 generators_.push_back(pGen);
                              } else {
                                 LOGE(id_ +
                                      ", no items available for generating "
                                      "solution");
                                 throw std::domain_error(
                                    __AT__ "MCT " + getID() +
                                    " no items available for "
                                    "generating solution");
                              }
                           } else {
                                  LOGE(id_ +
                                      ",  generator '" + pGen->getID() +
                                 "' type not allowed for adding");
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
      std::cerr << X.what() << std::endl;
   }
   catch (std::exception &X) {
      std::cerr << X.what() << std::endl;
   }
}

void GenExam::setLastItem()
{
   LOGD(type_ + ", " + id_);
   pLastAddedItem_->setAsLastItem();
}

void GenExam::generate(std::ostream &os)
{
   LOGD(type_ + ": " + id_);
   // GenItem::clearIndexCount();
   if (pLastAddedItem_) {
      pLastAddedItem_->setAsLastItem();
   }
   os << "% Start of exam '" << getID() << "' generation\n";
   if (nExams_s > 1) {
      os << "\\newpage\n\\setcounter{page}{1}\n\n";
   }
   std::shared_ptr<GenSolution> pGenSol(new GenSolution(this));
   pGenSol->setID(getID() + ".solution");
   add(pGenSol);

   for (auto &gen : generators_) {
      if (gen == nullptr) {
         LOGE(id_ + ", gen == nulptr");
      } else {
         gen->generate(os);
      }
   }
   LOGI(type_ + ": " + id_ + ", is generated");
   os << "\n% End of exam '" << getID() << "' generation\n\n";
}
