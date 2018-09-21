#ifndef GENOPTIONS_H
#define GENOPTIONS_H

#include <string>

#include "GenComposite.h"

class GenOption;

/// Represents a number of options and shared pre- and post processing
/// formatting. Contains a pre-processing and a post-processing string for
/// formatting all options at once. For example: set a column based format.
/// Class invariant: number of contained options >= 2
class GenOptions : public GenComposite
{
public:
   GenOptions();
   virtual ~GenOptions();

   virtual IGenPtr_t copy() const;
   virtual void add(IGenPtr_t pGen);
   virtual void generate(std::ostream &os);
   virtual std::ostream &write(std::ostream &os, int level = 0) const;

   /// Add an option
   void add(std::shared_ptr<GenOption> &pOption, bool isCorrect = false);
   /// Shuffle options in random order.
   void shuffle();
   /// Sort options on size.
   void sort();

   void setPreProcessing(const std::string &preProcessing)
   {
      preProcessing_ = preProcessing;
   }
   void setPostProcessing(const std::string &postProcessing)
   {
      postProcessing_ = postProcessing;
   }

private:
   std::string preProcessing_;
   std::string postProcessing_;
};

#endif