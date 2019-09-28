#include "GenExams.h"
#include "AppInfo.h"
#include "GenExam.h"
#include "Log.h"

#include <exception>

GenExams::GenExams(const std::string &id,
                   std::vector<Reader::message_t> &messages, int nExams)
   : ICompositeGenerator{id}
{
   type_ = __func__ + std::string("[]");
   for (int i = 0; i < nExams; ++i) {
      std::shared_ptr<GenExam> pExam(new GenExam(
         id_ + std::string("[" + std::to_string(i) + "]"), messages));
      generators_.push_back(pExam);
      // std::cout << *this << std::endl;
   }

   LOGD(id_ + ", intialised", 2);
}

void GenExams::generate(std::ostream &os)
{
   LOGD(type_ + ": '" + id_ + "'", 3);
   LOGCE(generators_.size() == 0, "no composite values available");

   os << "% Generated by " << APPNAME << " v" << VERSION << "\n\n";
   ICompositeGenerator::generate(os);
}

void GenExams::add(IGenPtr_t pGen)
{
   LOGD(type_ + ": '" + id_ + "', wants to add " + pGen->getType() + " " +
        pGen->getID(), 3);

   for (auto &gen : generators_) {
      gen->add(pGen->copy());
   }
}

std::ostream &GenExams::write(std::ostream &os, int level) const
{
   IGenerator::write(os, level);
   os << ": #Exams = " << generators_.size() << "\n";
   ICompositeGenerator::write(os, level + 1);
   return os;
}

void GenExams::setID(const std::string &id)
{
   LOGD(type_ + ": " + id_ + ", id = " + id, 3);

   int index = 0;

   id_ = id;
   for (auto &gen : generators_) {
      gen->setID(id + std::string("[" + std::string(1, ('0' + index++)) + "]"));
   }
}
