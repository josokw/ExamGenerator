#ifndef READER_H
#define READER_H

#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

class Builder;
class GenExams;

/// Responsible for reading and parsing the MCT specification
/// for creating a vector with pointers to #GenExams objects.
/// Part of Builder design pattern.
///
class Reader
{
public:
   /// char: S(ystem error), E(rror), W(arning), I(nfo)
   /// int: corresponding line number
   /// const char*: postion in input stream
   /// string: message contents
   using message_t = std::tuple<char, int, const char *, std::string>;

   Reader(std::istream &examScript);
   ~Reader() = default;

   void clear();
   /// Reads #examScriptText_ and adds a null char to end.
   void read();
   /// Returns parse result: vector of pointers to GenExams objects.
   /// This vector is empty if errors has occured during parsing.
   std::vector<std::shared_ptr<GenExams>> parse();
   /// Returns all parser messages (errors, info and warnings).
   const std::vector<message_t> &getMessages() const { return messages_; }

private:
   std::vector<message_t> messages_;
   std::istream &input_;
   std::vector<char> examScriptText_;
   Builder *pBuilder_;
};

#endif
