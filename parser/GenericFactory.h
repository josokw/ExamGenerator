#ifndef GENERICFACTORY_H
#define GENERICFACTORY_H

#include <map>
#include <memory>
#include <string>
#include <vector>

using defaultKey_t = std::string;

/// This template class is usable for creating concrete factory classes.
/// BaseTypeToBeManufactured must provide a virtual memberfunction create() for
/// polymorphic creating.
/// The Key class must be able to be used as a key in a std::map, i.e. it must:
///   - implement copy and assignment semantics
///   - provide 'bool operator<() const';
///
/// Default Key type is std::string. The factory becomes the owner of
/// registrated objects.
/// @short For creating concrete factory classes.
/// @author Jos Onokiewicz
template <class BaseTypeToBeManufactured, typename Key = defaultKey_t>
class GenericFactory
{
public:
   GenericFactory();
   virtual ~GenericFactory();

   /// Add new command to registry.
   void addToRegistry(const Key &key,
                      std::shared_ptr<BaseTypeToBeManufactured> tbm);
   /// Check registry if key is already registered.
   bool keyIsAlreadyRegistered(const Key &key) const;
   /// Registry will be cleared, all prototype objects will be dealocated.
   void clearRegistry();
   /// Client code is responsible for checking 0 valued returned pointer!
   std::shared_ptr<BaseTypeToBeManufactured> create(const Key &key) const;
   /// Retrieve all keys in a vector.
   std::vector<Key> getRegistryKeys() const;

private:
   typedef std::map<const Key, std::shared_ptr<BaseTypeToBeManufactured>>
      registry_t;
   typedef typename registry_t::iterator Ir_t;

   registry_t m_Registry;

   /// Not allowed, do not define.
   GenericFactory(const GenericFactory &f);
   /// Not allowed, do not define.
   GenericFactory &operator=(const GenericFactory &sf);
};

#include "GenericFactory_tmp.h"

#endif
