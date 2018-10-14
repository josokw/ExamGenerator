#include "Parser.h"
#include "Log.h"

int line = 0;

void print(const char *begin, const char *end)
{
   std::string str(begin, end);
   std::cout << "--- Info "
             << " " << line << ": " << str << std::endl;
}

void linecount(const char *, const char *)
{
   ++line;
}

// Helper functions
bool MCTestBuilder::idGeneratorIsUnique(const std::string &id,
                                        const char *begin,
                                        const char * /* end */)
{
   auto isUnique = true;
   if (find(generators_p, id.c_str())) {
      messages_.push_back(Reader::message_t(
         'E', 0, begin, "Generator '" + id + "' already exists."));
      isUnique = false;
   }
   return isUnique;
}

IGenPtr_t *MCTestBuilder::idGeneratorIsAvailable(const std::string &id,
                                                 const char *begin,
                                                 const char * /* end */)
{
   auto ppIGen = find(generators_p, id.c_str());
   if (0 == ppIGen) {
      messages_.push_back(Reader::message_t(
         'E', 0, begin, "Generator '" + id + "' does not exists."));
   }
   return ppIGen;
}

/// Error messages
/// @bug line number is not correct.
void MCTestBuilder::do_errorMessage(const char *begin, const char * /* end*/)
{
   switch (error) {
      case ERROR::NO:
         break;
      case ERROR::MCT_EXPECTED:
         messages_.push_back(Reader::message_t(
            'E', 0, begin, "MCT or MCT[] declaration expected."));
         break;
      case ERROR::CLOSING_BRACKET_EXPECTED:
         messages_.push_back(
            Reader::message_t('E', 0, begin, "Closing ] expected."));
         break;
      case ERROR::UNSIGNEDINT_EXPECTED:
         messages_.push_back(
            Reader::message_t('E', 0, begin, "Integer value expected."));
         break;
      case ERROR::SEMICOLON_EXPECTED:
         messages_.push_back(Reader::message_t('E', 0, begin, "; expected."));
         break;
      default:
         LOGE("line = " + std::to_string(line) + " unknown error code");
         messages_.push_back(
            Reader::message_t('S', 0, begin, "Unknown error code"));
         break;
   }
}
