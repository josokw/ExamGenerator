# ExamGenerator

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/be97a480b1114b2abfe83f4552011489)](https://www.codacy.com/app/josokw/ExamGenerator?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=josokw/ExamGenerator&amp;utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/josokw/examgenerator/badge)](https://www.codefactor.io/repository/github/josokw/examgenerator)

This application was developed about 10 jaars ago in ancient C++.
Now I have started to refactor the legacy code to C++17 and to use CMake.

This application reads a text script containing multiple choise questions
and compiles a LaTeX file.

A random generator is used to construct the questions and the answers.

## Building: using CMake and make

The application needs the next Boost C++ libraries:

- boost::spirit::classic
- boost::program_options
- boost::filesystem
  
For generating the pdf document the *pdflatex* application must be available.
Install LaTeX: *sudo apt install texlive-full*.

Go to the project root directory *ExamGenerator*.

Use *CMake* and *make* to build the application:

    mkdir build
    cd build
    cmake ..
    make

The excutable *ExamGenerator* can be found in the *bin* directory.

## Generating an exam pdf file

If the current directory is *build*, use the next command:

    ../bin/ExamGenerator -e ../examGenScripts/testDummyExam.exm

Use the *-s* option for the seed of the random generator (is reproducable):

    ../bin/ExamGenerator -e ../examGenScripts/testDummyExam.exm -s 1234

The file *testDummyExam.pdf* will be generated if no syntax errors have occurred in the exam script.

Use the *-d* option for generating detailed debug info in the *ExamGenerator.log* file:

    ../bin/ExamGenerator -e ../examGenScripts/testDummyExam.exm -d

## Syntax exam script language

Read the file *..../examGenScripts/testDummyExam3x.exm* for the syntax.

- Every .exm script should start with the declaration of an Exam object or an  array of fixed size of Exam objects.
- Every Exam should have a header, add 1 header to every Exam object.
- Every header has the next text fields: *school*, *course*, *lecturer*, *date* and *boxedtext*.
- Every exam question is represented by an *Item*.
- An exam consists of 1 or more items.
