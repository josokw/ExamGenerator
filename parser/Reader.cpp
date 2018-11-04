#include "Reader.h"
#include "GenExams.h"
#include "Log.h"
#include "Parser.h"

#include <algorithm>

namespace bsp = boost::spirit::classic;

Reader::Reader(std::istream &examScript)
   : messages_{}
   , input_{examScript}
   , examScriptText_{}
   , pBuilder_{nullptr}
{
}

void Reader::clear()
{
   examScriptText_.clear();
   messages_.clear();
}

void Reader::read()
{
   input_ >> std::noskipws;
   copy(std::istream_iterator<char>(input_), std::istream_iterator<char>(),
        back_inserter(examScriptText_));
   examScriptText_.push_back('\0');
}

std::vector<std::shared_ptr<GenExams>> Reader::parse()
{
   messages_.clear();
   ExamBuilder pb(messages_);
   skipparser skip;
   ExamSpecParser parser(pb);

   try {
      const static std::string LINE(75, '-');

      std::cout << "\n- Parsing started" << std::endl;
      std::cout << LINE << "\n";

      bsp::parse_info<> info = bsp::parse(&examScriptText_[0], parser, skip);

      if (info.full) {
         std::cout << LINE << "\n- Parsing ready\n" << LINE << "\n";
      } else {
         auto lineFailure =
            std::count(static_cast<const char *>(&examScriptText_[0]),
                       info.stop, '\n') +
            1;
         std::cerr << "\n\n"
                   << "*** Parsing failed at line: " << lineFailure << "\n"
                   << "*** stopped at:\n"
                   << info.stop << "\"\n\n";

         messages_.push_back(
            message_t('E', 0, info.stop, "syntax error, parsing failed"));
      }
   }
   catch (std::exception &x) {
      std::cerr << "SYSTEM ERROR " << x.what() << std::endl;
      messages_.push_back(message_t('S', 0, 0, x.what()));
   }
   catch (...) {
      std::cerr << "SYSTEM CRASH " << std::endl;
      messages_.push_back(message_t('S', 0, 0, ""));
   }

   for (auto &msg : messages_) {
      int lineNumber = 0;
      if (std::get<2>(msg) != 0) {
         lineNumber = std::count(static_cast<const char *>(&examScriptText_[0]),
                                 std::get<2>(msg), '\n') +
                      1;
      }
      std::get<1>(msg) = lineNumber;
   }

   for (auto const &msg : messages_) {
      std::cout << std::get<0>(msg) << " line " << std::get<1>(msg) << ": "
                << std::get<3>(msg) << std::endl;
      if (std::get<0>(msg) == 'E') {
         pb.Product.clear();
      }
   }

   return pb.getProduct();
}
