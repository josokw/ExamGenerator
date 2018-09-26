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
   typedef std::tuple<char, int, const char *, std::string> message_t;

   Reader(std::istream &inputSpec);
   ~Reader() = default;

   void clear();
   /// Reads #textSpec and adds a null char to end.
   void read();
   /// Returns parse result: vector of pointers to GenExams objects.
   /// This vector is empty if errors has occured during parsing.
   std::vector<std::shared_ptr<GenExams>> parse();
   /// Returns all parser messages (errors, info and warnings).
   const std::vector<message_t> getMessages() const { return messages; }

private:
   std::vector<message_t> messages;
   std::istream &input;
   std::vector<char> textSpec;
   Builder *pBuilder;
};

#endif
