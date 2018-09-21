#ifndef EXCINFO_H
#define EXCINFO_H

#include <boost/filesystem.hpp>

#define STRINGIZE(x) STRINGIZE_(x)
#define STRINGIZE_(x) #x
#define __AT__ " "

//    boost::filesystem::path(__FILE__).filename().string() +
//       " " __func__ ":" STRINGIZE(__LINE__) " "

// Usage: throw std::runtime_error(__AT__ "Problems #$#^%^!!");

#endif
