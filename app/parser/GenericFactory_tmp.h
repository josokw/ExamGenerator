//-----------------------------------------------------------------------
//GenericFactory_tmp.h

template <class BaseTypeToBeManufactured, typename Key>
GenericFactory<BaseTypeToBeManufactured, Key>::GenericFactory()
{
}

template <class BaseTypeToBeManufactured, typename Key>
GenericFactory<BaseTypeToBeManufactured, Key>::~GenericFactory()
{
}

template <class BaseTypeToBeManufactured, typename Key>
void GenericFactory<BaseTypeToBeManufactured, Key>::addToRegistry(
   const Key &key, std::shared_ptr<BaseTypeToBeManufactured> pTbm)
{
   m_Registry[key] = pTbm;
}

template <class BaseTypeToBeManufactured, typename Key>
bool GenericFactory<BaseTypeToBeManufactured, Key>::keyIsAlreadyRegistered(
   const Key &key) const
{
   return m_Registry.find(key) != m_Registry.end();
}

template <class BaseTypeToBeManufactured, typename Key>
void GenericFactory<BaseTypeToBeManufactured, Key>::clearRegistry()
{
   Ir_t I = m_Registry.begin();

   while (I != m_Registry.end()) {
      // delete I->second;
      ++I;
   }
   m_Registry.clear();
}

template <class BaseTypeToBeManufactured, typename Key>
std::shared_ptr<BaseTypeToBeManufactured>
GenericFactory<BaseTypeToBeManufactured, Key>::create(const Key &key) const
{
   std::shared_ptr<BaseTypeToBeManufactured> pTbm;

   typename registry_t::const_iterator iter = m_Registry.find(key);

   if (iter != m_Registry.end()) {
      pTbm = iter->second->copy();
   }

   return pTbm; // Client code is responsible for checking 0 value!
}

template <class BaseTypeToBeManufactured, typename Key>
std::vector<Key>
GenericFactory<BaseTypeToBeManufactured, Key>::getRegistryKeys() const
{
   std::vector<Key> RegistryKeys;
   typename registry_t::const_iterator iter;

   for (iter = m_Registry.begin(); iter != m_Registry.end(); ++iter) {
      RegistryKeys.push_back(iter->first);
   }

   return RegistryKeys;
}
