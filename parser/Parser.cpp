#include "Parser.h"

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
bool MCTestBuilder::idGeneratorIsUnique(const string &id, const char *begin,
                                        const char * /* end */)
{
   auto isUnique = true;
   if (find(generators_p, id.c_str())) {
      messages.push_back(Reader::message_t(
         'E', 0, begin, "Generator '" + id + "' already exists."));
      isUnique = false;
   }
   return isUnique;
}

IGenPtr_t *MCTestBuilder::idGeneratorIsAvailable(const string &id,
                                                 const char *begin,
                                                 const char * /* end */)
{
   auto ppIGen = find(generators_p, id.c_str());
   if (0 == ppIGen) {
      messages.push_back(Reader::message_t(
         'E', 0, begin, "Generator '" + id + "' does not exists."));
   }
   return ppIGen;
}

// Error functions
void MCTestBuilder::do_errorMessage(const char *begin, const char * /* end*/)
{
   switch (error) {
      case NO_ERROR:
         break;
      case ERR_MCT_EXPECTED:
         messages.push_back(Reader::message_t(
            'E', 0, begin, "MCT or MCT[] declaration expected."));
         break;
      case ERR_CLOSING_BRACKET_EXPECTED:
         messages.push_back(
            Reader::message_t('E', 0, begin, "Closing ] expected."));
         break;
      case ERR_UNSIGNEDINT_EXPECTED:
         messages.push_back(
            Reader::message_t('E', 0, begin, "Integer value expected."));
         break;
      case ERR_SEMICOLON_EXPECTED:
         messages.push_back(Reader::message_t('E', 0, begin, "; expected."));
         break;
      default:
         messages.push_back(
            Reader::message_t('S', 0, begin, "Unknown error code"));
   }
}