#ifndef EXAMGENERATORCONFIG_H
#define EXAMGENERATORCONFIG_H

#include "AppInfo.h"

#include <string>

const std::string LOG_FILENAME{APPNAME ".log"};
const std::string EXAM_LATEX_FILENAME{"../LaTeX/examDoc.tex"};
const std::string EXAM_ANSWERS_LATEX_FILENAME{"../LaTeX/examAnswersDoc.tex"};

const long int SEED_DEFAULT{123456789L};

#endif