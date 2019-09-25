#ifndef GENERICFACTORY_H
#define GENERICFACTORY_H

#include <map>
#include <memory>
#include <string>
#include <vector>

/// This template class is usable for creating concrete factory classes.
/// IType must provide a virtual memberfunction create() for
/// polymorphic creating.
/// The Key class must be able to be used as a key in a std::map, i.e. it must:
///   - implement copy and assignment semantics
///   - provide 'bool operator<() const';
///
/// Default Key type is std::string. The factory becomes the owner of
/// registrated objects.
///
/// \short Template class for creating concrete factory classes.
template <typename IType, typename KeyType = std::string>
class GenericFactory final
{
public:
   GenericFactory() = default;
   GenericFactory(const GenericFactory &) = delete;
   GenericFactory &operator=(const GenericFactory &) = delete;
   GenericFactory(const GenericFactory &&) = delete;
   GenericFactory &operator=(const GenericFactory &&) = delete;
   ~GenericFactory() = default;

   void addToRegistry(const KeyType &key, std::shared_ptr<IType> pIType)
   {
      registry_[key] = std::move(pIType);
   }

   /// Check registry if key is already registered.
   bool keyIsAlreadyRegistered(const KeyType &key) const
   {
      return registry_.find(key) != end(registry_);
   }

   /// Client code is responsible for checking 0 valued returned pointer!
   std::shared_ptr<IType> create(const KeyType &key) const
   {
      std::shared_ptr<IType> pIType{nullptr};
      auto iter = registry_.find(key);

      if (iter != end(registry_)) {
         pIType = iter->second->copy();
      }

      return pIType;
   }

private:
   std::map<const KeyType, std::shared_ptr<IType>> registry_;
};

#endif
