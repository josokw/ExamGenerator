#ifndef IGENERATOR_H
#define IGENERATOR_H

#include "Log.h"
#include "RandomProfile.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class IGenerator;

using IGenPtr_t = std::shared_ptr<IGenerator>;

/// Abstract interface class for all generating classes. Every generating class
/// must generate a result to an output stream after a preparation step by
/// #prepare() and a second step by #generate(). For transparency the
/// child management of composites is implemented in ICompositeGenerator to
/// treat all components (leafs and composites) uniformly. Leaf types should not
/// call add().
///
/// Contains a shared #randomProfile_s object for generating a number of
/// integers for selecting input values.
///
/// Class invariant: #id_ is not empty.
///
/// @todo make class non-copyable
class IGenerator
{
   friend std::ostream &operator<<(std::ostream &os, const IGenerator &iGen);

public:
   IGenerator();
   explicit IGenerator(std::string_view id);
   virtual ~IGenerator();
   //    IGenerator(const IGenerator &other) = delete;
   IGenerator &operator=(const IGenerator &other) = delete;
   //    IGenerator(IGenerator &&other) = delete;

   /// Copies IGenerator derived class instantiations.
   virtual IGenPtr_t copy() const = 0;
   /// Adds another IGenerator derived type object to composite types.
   virtual void add(IGenPtr_t pGen) = 0;
   /// Prepares strings used by #generate(). Default empty.
   virtual void prepare(){};
   /// Generates text.
   virtual void generate(std::ostream &os) = 0;
   /// Writes status to os stream.
   virtual std::ostream &write(std::ostream &os, int level = 0) const;

   std::string getType() const { return type_; }
   void setID(std::string_view id);
   std::string getID() const { return id_; }
   void setLevel(int level);
   int getLevel() const { return level_; }

protected:
   /// Shared random generator.
   static RandomProfile randomProfile_s;
   /// Vector containing ranges data.
   std::vector<RandomProfile::range_t> ranges_;
   /// Vector containing results of generated values based on ranges_.
   std::vector<int> RSelectors_;
   /// ID generator type
   std::string type_;
   /// ID generator name.
   std::string id_;
   /// Level of question: 0 not defined, 1 lowest level , 2 ...
   int level_;
};

#endif
