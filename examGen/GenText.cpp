#include <string> 

#include "GenText.h"
#include "Log.h"

using namespace std;

GenText::GenText(const std::string& text)
  : text_(text)
{
  type_ = "GenText";
  LOGD(id_ + " initialised");
}

GenText::~GenText()
{
  //IGenerator::write(clog) << " ##### DTOR" << endl;
}

IGenPtr_t GenText::copy() const
{
  std::shared_ptr<GenText> p(new GenText(*this)); 
  return p;
}

std::ostream& GenText::write(std::ostream& os, int Level) const
{
  IGenerator::write(os, Level);
  os << ": " << text_.substr(0, 25) << "...\n";
  return os;
}

void GenText::generate(std::ostream& os)
{
  os << '{' << text_ << '}';     
}
