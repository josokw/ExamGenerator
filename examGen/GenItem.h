#ifndef GENITEM_H
#define GENITEM_H

#include <memory>
#include <string>
#include <vector>

#include "GenComposite.h"
#include "RandomProfile.h"

class GenStem;
class GenOption;

/// Represents an multiple choice (MC) test item.
/// An item always contains 1 stem #GenStem and several options in a #GenOptions
/// object. Client code must set the index, setIndex(), used in the generated
/// text. Options can be randomly shuffled before generating if this option
/// switched on by calling #shuffleON().
class GenItem : public GenComposite
{
public:
   GenItem();
   GenItem(const std::string &id);
   virtual ~GenItem();

   virtual IGenPtr_t copy() const;
   virtual void add(IGenPtr_t pGen);
   virtual void generate(std::ostream &os);
   virtual std::ostream &write(std::ostream &os, int Level = 0) const;

   void addToStem(IGenPtr_t pGen);
   void setIndex(int index);
   void setAsLastItem() const;
   void addToOptions(std::shared_ptr<GenOption> pOption,
                     bool isCorrect = false);
   void setPreProOptions(const std::string &preProcessing);
   void setPostProOptions(const std::string &postProcessing);
   void setLevel(int level);

   /// Set shuffle status for generating options
   void shuffleON();
   /// Sort options on size.
   void sortOptions();

protected:
   virtual void prepare();

private:
   int index_;
   mutable bool isLastItem_;
   int level_;
   bool shuffleON_;
};

#endif
