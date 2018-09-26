#include "GenSolution.h"
#include "GenExam.h"
#include "GenItem.h"
#include "GenOption.h"
#include "GenOptions.h"
#include "Log.h"

#include <iostream>

GenSolution::GenSolution(GenExam *pExam)
   : IGenerator()
   , pExam_{pExam}
   , solutions_{}
{
   type_ = "GenSolution";
   LOGD(id_ + ", initialised");
}

GenSolution::~GenSolution()
{
   LOGD(id_);
}

IGenPtr_t GenSolution::copy() const
{
   LOGD(id_);
   std::shared_ptr<GenSolution> p(new GenSolution(*this));
   return p;
}

std::ostream &GenSolution::write(std::ostream &os, int Level) const
{
   IGenerator::write(os, Level);
   os << ": for exam '" << pExam_->getID() << "' size " << solutions_.size()
      << "\n";
   os << "\\\\Oplossing:\n";
   for (size_t i = 0; i < solutions_.size(); ++i) {
      os << "\\\\ " << (i + 1) << ". " << static_cast<char>('A' + solutions_[i])
         << "\n";
   }
   return os;
}

void GenSolution::prepare()
{
   LOGD(id_);
   auto size = pExam_->size();
   for (size_t i = 0; i < size; ++i) {
      IGenPtr_t pIGen = (*pExam_)[i];
      if (std::shared_ptr<GenItem> pItem =
             std::dynamic_pointer_cast<GenItem>(pIGen)) {
         std::cerr << *(*pExam_)[i] << std::endl;
         std::shared_ptr<GenOptions> pOptions =
            std::static_pointer_cast<GenOptions>((*pItem)[1]);
         for (size_t k = 0; k < pOptions->getGenerators().size(); ++k) {
            if (std::shared_ptr<GenOption> pOption =
                   std::dynamic_pointer_cast<GenOption>((*pOptions)[k])) {
               if (pOption->getIsCorrect()) {
                  solutions_.push_back(k);
               }
            }
         }
      }
   }
   std::cerr << *this << std::endl;
}

void GenSolution::generate(std::ostream &os)
{
   LOGD(id_);
   prepare();

   os << "\n% Solution generation for MCT '" + pExam_->getID() + "'\n";
   os << "\\cleardoublepage\n";
   os << "\\noindent " << std::string(40, '-') << "  " << pExam_->getID()
      << "\n";
   os << "\\\\Oplossing:\n";
   for (size_t i = 0; i < solutions_.size(); ++i) {
      os << "\\\\ " << (i + 1) << ". " << static_cast<char>('A' + solutions_[i])
         << "\n";
   }
   os << "\\\\ " << std::string(40, '-')
      << std::string(2 + pExam_->getID().size(), '-') << "\n";
}
