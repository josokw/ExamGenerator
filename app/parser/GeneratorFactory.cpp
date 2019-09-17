#include "GeneratorFactory.h"
#include "IGenerator.h"

#include <iostream>

/// Sets FNAME to the name of a function.
/// FNAME is a static local string constant in the corresponding function.
#define SET_FNAME(name) static const char *const FNAME = name
#define ID_FNAME "'" + m_ID + "'  " + string(FNAME)

using namespace std;

GeneratorFactory::GeneratorFactory() {}

GeneratorFactory::~GeneratorFactory() {}

IGenPtr_t GeneratorFactory::create(const std::string &Key) const
{
   return m_Factory.create(Key);
}

void GeneratorFactory::addGenerator(const std::string &Key,
                                    IGenPtr_t pGenerator)
{
   if (m_Factory.keyIsAlreadyRegistered(Key)) {
      // throw XSyntax("Command identifier '" + Key + "' is not unique, "
      //  "already registered");
      //  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
   }
   m_Factory.addToRegistry(Key, pGenerator);
}

/*
void GeneratorFactory::addCommand(const GeneratorFactory* pCF)
{
  std::vector<std::string> RegistryKeys = pCF->GetCommandStrings();
  for (std::vector<std::string>::const_iterator it = RegistryKeys.begin();
    it != RegistryKeys.end();
    ++it)
  {
    AddCommand(*it, pCF->Create(*it));
  }
  cout << ID_FNAME + " added '" + pCF->GetID() + "'" << endl;
}

std::vector<std::string> GeneratorFactory::GetCommandStrings() const
{
  return m_Factory.GetRegistryKeys();
}

std::vector<std::string> GeneratorFactory::GetFullCommandStrings() const
{
  std::vector<std::string> FullCommands;

  std::vector<std::string> CommandStrings = GetCommandStrings();
  for (std::vector<std::string>::const_iterator Command =
CommandStrings.begin(); Command != CommandStrings.end();
    ++Command)
  {
    std::string FullCommandString(*Command);

    FullCommandString += "(";
    int i = 0;
    std::vector<std::string> Parameters = Create(*Command)->GetParameterTypes();
    for (std::vector<std::string>::const_iterator it = Parameters.begin();
      it != Parameters.end();
      ++it)
    {
      if (i > 0)
      {
        FullCommandString += ", ";
      }
      ++i;
      FullCommandString += "<" + *it + ">";
    }
    FullCommandString += ");";
    FullCommands.push_back(FullCommandString);
  }

  return FullCommands;
}
*/

void GeneratorFactory::clear()
{
   m_Factory.clearRegistry();
}