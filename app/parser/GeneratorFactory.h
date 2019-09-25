#ifndef GENERATORFACTORY_H
#define GENERATORFACTORY_H

#include <string>
#include <vector>

#include "GenericFactory.h"
#include "IGenerator.h"

/// The class 'GeneratorFactory' is responsible for creating IGenerator derived
/// objects. The key for creating is a string. Related to the 'Factory Method'
/// desing pattern. The factory becomes the owner of the registrated IGenerator
/// objects.
/// \short Responsible for creating IGenerator derived type objects.
class GeneratorFactory final
{
public:
   GeneratorFactory() = default;
   ~GeneratorFactory() = default;

   /// \short Create a IGenerator derived object by its key.
   /// \param Key string representing the generator.
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
