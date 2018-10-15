#ifndef IGENERATOR_H
#define IGENERATOR_H

#include "RandomProfile.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class IGenerator;

using IGenPtr_t = std::shared_ptr<IGenerator>;

/// Abstract interface class for all generating classes. Every generating class
/// must generate a result to an output stream after a preparation step by
/// #prepare() and a second step by #generateContens(). For transparency the
/// child management of composites is implemented in IGenerator to treat all
/// components (leafs and composites) uniformly. Leaf types should not call
/// add(), if called this will throw an exeption.
///
/// Contains a shared #randomProfile_s object for generating a number of
/// integers for selecting input values.
///
/// Class invariant: #id_ is not empty.
class IGenerator
{
   friend std::ostream &operator<<(std::ostream &os, const IGenerator &iGen);

public:
   IGenerator();
   explicit IGenerator(const std::string &id);
   virtual ~IGenerator();

   /// Copies IGenerator derived class instantiations.
   virtual IGenPtr_t copy() const = 0;
   /// Adds another IGenerator derived type object to composite types.
   /// Leaf types will generate an exception (default implementation).
   virtual void add(IGenPtr_t pGen);

   /// Generates text.
   virtual void generate(std::ostream &os) = 0;
   /// Writes status to os stream.
   virtual std::ostream &write(std::ostream &os, int level = 0) const;
   const std::string &getType() const { return type_; }
   void setID(const std::string &id) { id_ = id; }
   const std::string &getID() const { return id_; }
   void setDifficultyLevel(int difficultyLevel)
   {
      difficultyLevel_ = difficultyLevel;
   }
   int getDifficultyLevel() const { return difficultyLevel_; }

protected:
   /// Shared random generator.
   static RandomProfile randomProfile_s;
   /// Vector containing ranges data.
   std::vector<Random::range_t> ranges_;
   /// Vector containing results of generated values based on ranges_.
   std::vector<int> RSelectors_;
   /// ID generator type
   std::string type_;
   /// ID generator name.
   std::string id_;
   /// Difficulty level of question: 0 not defined, 1 lowest level , 2 ...
   int difficultyLevel_;

public:
   /// Prepares strings used by #generateContents().
   /// Default empty.
   virtual void prepare() {}
};

#endif
