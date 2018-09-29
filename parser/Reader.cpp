#include "Reader.h"
#include "GenExams.h"
#include "Log.h"
#include "Parser.h"

#include <algorithm>

namespace bsp = boost::spirit::classic;

Reader::Reader(std::istream &inputSpec)
   : input(inputSpec)
{
}

void Reader::clear()
{
   textSpec.clear();
   messages.clear();
}

void Reader::read()
{
   input >> std::noskipws;
   copy(std::istream_iterator<char>(input), std::istream_iterator<char>(),
        back_inserter(textSpec));
   textSpec.push_back(0);
   for (auto c : textSpec) {
      std::cout << c;
   }
}

std::vector<std::shared_ptr<GenExams>> Reader::parse()
{
   messages.clear();
   MCTestBuilder pb(messages);
   skipparser skip;
   MCTspecParser parser(pb);

   try {
      const static std::string LINE(75, '-');
      std::cout << "\n- Parsing started" << std::endl;
      std::cout << LINE << "\n";

      bsp::parse_info<> info = bsp::parse(&textSpec[0], parser, skip);

      if (info.full) {
         std::cout << LINE << "\n- Parsing ready\n" << LINE << "\n";
      } else {
         size_t line = std::count(static_cast<const char *>(&textSpec[0]),
                                  info.stop, '\n') +
                       1;
         std::cout << "\n\n";
         std::cout << "*** Parsing failed at line: " << line << "\n";
         std::cout << "*** stopped at:\n" << info.stop << "\"\n\n";

         messages.push_back(
            message_t('E', 0, info.stop, "syntax error, parsing failed"));
      }
   }
   catch (std::exception &x) {
      std::cerr << "SYSTEM ERROR " << x.what() << std::endl;
      messages.push_back(message_t('S', 0, 0, x.what()));
   }
   catch (...) {
      std::cerr << "SYSTEM CRASH " << std::endl;
      messages.push_back(message_t('S', 0, 0, ""));
   }

   for (size_t i = 0; i < messages.size(); ++i) {
      int lineNumber = 0;
      if (std::get<2>(messages[i]) != 0) {
         lineNumber = std::count(static_cast<const char *>(&textSpec[0]),
                                 std::get<2>(messages[i]), '\n') +
                      1;
      }
      std::get<1>(messages[i]) = lineNumber;
   }

   for (size_t i = 0; i < messages.size(); ++i) {
      std::cout << std::get<0>(messages[i]) << " line "
                << std::get<1>(messages[i]) << ": " << std::get<3>(messages[i])
                << std::endl;
      if (std::get<0>(messages[i]) == 'E') {
         pb.Product.clear();
      }
   }

   return pb.getProduct();
}
