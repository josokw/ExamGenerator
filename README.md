# ExamGenerator

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/be97a480b1114b2abfe83f4552011489)](https://www.codacy.com/app/josokw/ExamGenerator?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=josokw/ExamGenerator&amp;utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/josokw/examgenerator/badge)](https://www.codefactor.io/repository/github/josokw/examgenerator)

This application was developed about 10 jaars ago in ancient C++.
Now I have started to refactor the code to C++14 and using CMake.

This application reads a text script containing multiple choise questions
and compiles a LaTeX file.

A random generator is used to construct the questions and the answers.

## Building: using CMake and make

The application needs the Boost Spirit Classic library.
For generating the pdf document the *pdflatex* application must be available.

Go to the project root directory ExamGenerator.

Use *CMake* and *make* to build the application:

    mkdir build
    cd build
    cmake ..
    make

The excutable can be found in the *bin* directory.

## Generating an exam

If the current directory is *build*, use the next command:

    ../bin/ExamGenerator -e ../examGenScripts/testDummyExam.exm

A pdf will be generated if no syntax errors has occurred.
