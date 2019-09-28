#ifndef GENCFACTORY_H
#define GENCFACTORY_H

#include "GenCFactory.h"
#include "GenericFactory.h"
#include "IGenerator.h"

#include <string>
#include <vector>

/// The class 'GenCFactory' is responsible for creating IGenerator derived
/// objects. The key for creating is a string. Related to the 'Factory Method'
/// desing pattern. The factory becomes the owner of the registrated IGenerator
/// objects.
/// \short Responsible for creating IGenerator derived type objects.
class GenCFactory final
{
public:
   GenCFactory();
   ~GenCFactory() = default;

   /// \short Create a IGenerator derived object by its key.
   /// \param key string representing the generator.
   /// \returns IGenPtr_t pointer to created generator.
   IGenPtr_t create(const std::string &key) const;

   /// \short Add IGenerator derived objects (prototypes) and the related key
   /// to the factory.
   void addGenerator(const std::string &key, IGenPtr_t pGenerator);

   /// \short Remove all dynamically created prototypes.
   void clear();

private:
   GenericFactory<IGenerator> factory_;
};

#endif
