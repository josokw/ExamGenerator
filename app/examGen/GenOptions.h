#ifndef GENOPTIONS_H
#define GENOPTIONS_H

#include "GenRandom.h"
#include "ICompositeGenerator.h"

class GenOption;

/// Represents a number of options and shared pre- and post processing
/// formatting. Contains a pre-processing and a post-processing string for
/// formatting all options at once. For example: set a column based format.
/// Class invariant: number of contained options >= 2
class GenOptions : public ICompositeGenerator
{
public:
   GenOptions(std::string_view id);
   ~GenOptions() override = default;

   [[nodiscard]] IGenPtr_t copy() const override;
   void add(IGenPtr_t pGen) override;
   void generate(std::ostream &os) override;
   std::ostream &write(std::ostream &os, int level = 0) const override;

   /// Add an option
   void add(std::shared_ptr<GenOption> &pOption, bool isCorrect = false);
   /// Shuffle options in random order.
   void shuffle();
   /// Sort options on size.
   void sort();

   void setPreProcessing(std::string_view preProcessing)
   {
      preProcessing_ = preProcessing;
   }
   void setPostProcessing(std::string_view postProcessing)
   {
      postProcessing_ = postProcessing;
   }

private:
   static GenRandom genrnd_s;
   std::string preProcessing_;
   std::string postProcessing_;
};

#endif
