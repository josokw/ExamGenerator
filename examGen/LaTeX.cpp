#include <boost/lexical_cast.hpp>

#include "LaTeX.h"
#include "Util.h"

using namespace std;

std::string latex::LogicBlock(const std::string &Type, int posX, int posY,
                              int size)
{
   string Result;

   Result = "\\put(" + boost::lexical_cast<string>(posX) + "," +
            boost::lexical_cast<string>(posY) + "){\\line(0,1){" +
            boost::lexical_cast<string>(size) +
            "}}\n"
            "\\put(" +
            boost::lexical_cast<string>(posX + size) + "," +
            boost::lexical_cast<string>(posY) + " ){\\line(0,1){" +
            boost::lexical_cast<string>(size) +
            "}}\n"
            "\\put(" +
            boost::lexical_cast<string>(posX) + "," +
            boost::lexical_cast<string>(posY) + "){\\line(1,0){" +
            boost::lexical_cast<string>(size) +
            "}}\n"
            "\\put(" +
            boost::lexical_cast<string>(posX) + "," +
            boost::lexical_cast<string>(posY + size) + "){\\line(1,0){" +
            boost::lexical_cast<string>(size) +
            "}}\n"

            "\\put(" +
            boost::lexical_cast<string>(posX + size / 2) + "," +
            boost::lexical_cast<string>(posY + size / 2) +
            "){\\makebox(0,0)[cc]{" + Type + "}}\n";

   return Result;
}

std::string latex::LogicEquate(int posX, int posY, int size)
{
   string Result;
   Result = "\\put(" + boost::lexical_cast<string>(posX) + "," +
            boost::lexical_cast<string>(posY) + "){\\line(1,0){" +
            boost::lexical_cast<string>(size) + "}}\n";

   return Result;
}
