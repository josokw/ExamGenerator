#ifndef LATEX_H
#define LATEX_H

#include <string>

namespace latex {

std::string LogicBlock(std::string_view type, int posX, int posY, int size);
std::string LogicEquate(int posX, int posY, int size);

} // namespace latex

#endif
