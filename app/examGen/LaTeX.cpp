#include "LaTeX.h"
#include "Util.h"

#include <string>

std::string latex::LogicBlock(std::string_view Type, int posX, int posY,
                              int size)
{
   std::string result;

   result = "\\put(" + std::to_string(posX) + "," + std::to_string(posY) +
            "){\\line(0,1){" + std::to_string(size) +
            "}}\n"
            "\\put(" +
            std::to_string(posX + size) + "," + std::to_string(posY) +
            " ){\\line(0,1){" + std::to_string(size) +
            "}}\n"
            "\\put(" +
            std::to_string(posX) + "," + std::to_string(posY) +
            "){\\line(1,0){" + std::to_string(size) +
            "}}\n"
            "\\put(" +
            std::to_string(posX) + "," + std::to_string(posY + size) +
            "){\\line(1,0){" + std::to_string(size) +
            "}}\n"

            "\\put(" +
            std::to_string(posX + size / 2) + "," +
            std::to_string(posY + size / 2) + "){\\makebox(0,0)[cc]{" + Type +
            "}}\n";

   return result;
}

std::string latex::LogicEquate(int posX, int posY, int size)
{
   std::string result = "\\put(" + std::to_string(posX) + "," +
                        std::to_string(posY) + "){\\line(1,0){" +
                        std::to_string(size) + "}}\n";

   return result;
}
