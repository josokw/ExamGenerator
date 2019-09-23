#include "Parser.h"
#include "Log.h"
#include "Util.h"

int line = 0;

void linecount(const char *, const char *)
{
   ++line;
}

// Helper functions
bool ExamBuilder::idGeneratorIsUnique(const std::string &id, const char *begin,
                                      const char * /* end */)
{
   auto context = util::removeNewLines(util::limitSize(begin, 60));
   auto isUnique = true;

   if (find(generators_p, id.c_str())) {
      LOGE("generator '" + id + "' already exists, line = " + context);
      messages_.push_back(Reader::message_t(
         'E', 0, begin, "Generator '" + id + "' already exists."));
      isUnique = false;
   }
   return isUnique;
}

IGenPtr_t *ExamBuilder::idGeneratorIsAvailable(const std::string &id,
                                               const char *begin,
                                               const char *end)
{
   // auto context = util::removeNewLines(util::limitSize(begin, 60));
   auto ppIGen = bsc::find(generators_p, id.c_str());

   if (nullptr == ppIGen) {
      LOGE("generator '" + id +
           "' does not exists, line = " + std::to_string(line));
      messages_.push_back(Reader::message_t(
         'E', 0, begin, "Generator '" + id + "' does not exists."));
   }
   return ppIGen;
}

/// Error messages
/// @bug line number is not correct.
void ExamBuilder::do_errorMessage(const char *begin, const char * /* end*/)
{
   auto context = util::removeNewLines(util::limitSize(begin, 60));

   switch (error_) {
      case ERROR::NO:
         break;
      case ERROR::EXM_EXPECTED:
         messages_.push_back(Reader::message_t(
            'E', 0, context.c_str(), "Exam or Exam[] declaration expected."));
         break;
      case ERROR::CLOSING_BRACKET_EXPECTED:
         messages_.push_back(
            Reader::message_t('E', 0, context.c_str(), "Closing ] expected."));
         break;
      case ERROR::UNSIGNEDINT_EXPECTED:
         messages_.push_back(Reader::message_t('E', 0, context.c_str(),
                                               "Integer value expected."));
         break;
      case ERROR::SEMICOLON_EXPECTED:
         messages_.push_back(
            Reader::message_t('E', 0, context.c_str(), "; expected."));
         break;
      default:
         LOGE(
            "unknown error code = " + std::to_string(static_cast<int>(error_)) +
            ", in line: " + context);
         messages_.push_back(
            Reader::message_t('S', 0, context.c_str(),
                              "Unknown error code = " +
                                 std::to_string(static_cast<int>(error_))));
         break;
   }
}
