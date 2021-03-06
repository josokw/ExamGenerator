#include "AppInfo.h"
#include "ExamGeneratorConfig.h"
#include "GenCodeText.h"
#include "GenExams.h"
#include "GenHeader.h"
#include "GenNull.h"
#include "GenText.h"
#include "Log.h"
#include "RandomProfile.h"
#include "Reader.h"
#include "Seed.h"

#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/program_options.hpp>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

namespace bpo = boost::program_options;
namespace bfs = boost::filesystem;

std::tuple<bfs::path> processCLI(int argc, char *argv[]);

/// \todo Implement generating answers pdf document.
int main(int argc, char *argv[])
{
   try {
      LOGI(APPNAME " v" VERSION " started");

      bfs::path currentInitialDir(bfs::initial_path());
      auto [examScriptFileName] = processCLI(argc, argv);

      std::cout << "- " << APPNAME << " v" << VERSION << " started in "
                << currentInitialDir << std::endl;

      const bfs::path LaTeXoutputDir(".");
      const bfs::path LaTeXgeneratedExamFileName(LaTeXoutputDir /
                                                 "generatedExam.tex");
      //   const bfs::path LaTeXgeneratedExamAnswersFileName(
      //      LaTeXoutputDir / "generatedExamAnswers.tex");

      LOGI("Generated LaTeX exam file: " +
           (LaTeXoutputDir / "generatedExam.tex").string());
      //   LOGI("Generated LaTeX exam answers file: " +
      //        (LaTeXoutputDir / "generatedExamAnswers.tex").string());

      const bfs::path LaTeXdocExamFileName(EXAM_LATEX_FILENAME);
      const bfs::path LaTeXdocExamAnswersFileName(EXAM_ANSWERS_LATEX_FILENAME);

      const bfs::path ExamPDFfilename{examScriptFileName.filename().stem()};

      const std::string LaTeXcommandExam{
         "pdflatex -enable-write18 -jobname=" + ExamPDFfilename.string() +
         "-answers \"-output-directory=" + LaTeXoutputDir.string() + "\" " +
         (LaTeXoutputDir / LaTeXdocExamFileName).string() + " 2>&1 /dev/null"};

      //   const std::string LaTeXcommandExamAnswers(
      //      "pdflatex -enable-write18 \"-output-directory=" +
      //      LaTeXoutputDir.string() + "\" " +
      //      (LaTeXoutputDir / LaTeXdocExamAnswersFileName).string() +
      //      " 2>&1 /dev/null");

      bfs::ofstream LaTeXgeneratedExamFile{LaTeXgeneratedExamFileName};
      if (!LaTeXgeneratedExamFile) {
         LOGE("Generated LaTeX exam file '" +
              LaTeXgeneratedExamFileName.string() + "' does not exists");
         std::cerr << "\n\tERROR: generated LaTeX exam file '"
                   << LaTeXgeneratedExamFileName.string()
                   << "' does not exists\n\n";
         exit(EXIT_FAILURE); //================================================>
      }
      //   bfs::ofstream LaTeXgeneratedExamAnswersFile(
      //      LaTeXgeneratedExamAnswersFileName);
      //   if (!LaTeXgeneratedExamAnswersFile) {
      //      LOGE("Generated LaTeX exam answers file '" +
      //           LaTeXgeneratedExamAnswersFileName.string() + "' does not
      //           exists");
      //      std::cerr << "\n\tERROR: generated LaTeX exam answers file '"
      //                << LaTeXgeneratedExamAnswersFileName.string()
      //                << "' does not exists\n\n";
      //      exit(EXIT_FAILURE);
      //      //================================================>
      //   }

      bfs::ifstream examScriptFile{examScriptFileName};
      if (!examScriptFile) {
         LOGE("Exam script file '" + examScriptFileName.string() +
              "' does not exists");
         std::cerr << "\n\tERROR: exam script file '"
                   << examScriptFileName.string() << "' does not exists\n\n";
         exit(EXIT_FAILURE); //================================================>
      }

      // Start generating exam based on script
      LOGI("Start reading exam script: " + examScriptFileName.string());
      Reader reader{examScriptFile};
      reader.read();

      auto scriptedTests{reader.parse()};

      if (!scriptedTests.empty()) {
         std::cout << "- Generating scripted exams" << std::endl;

         LOGI("Start generating LaTeX exam file: " +
              LaTeXgeneratedExamFileName.string());
         for (auto &st : scriptedTests) {
            st->generate(LaTeXgeneratedExamFile);
         }

         LaTeXgeneratedExamFile.close();
         //  LaTeXgeneratedExamAnswersFile.close();
         LOGI("Generated LaTeX file: " + LaTeXgeneratedExamFileName.string());

         std::cout << "- LaTeX file generated\n";
         std::cout << "- Started PDF exam file generation\n";
         LOGI("LaTeX to pdf command: " + LaTeXcommandExam);
         // Generate DVI file
         system(LaTeXcommandExam.c_str());
         std::cout << "\n- PDF exam file generated\n\n";
         //  system(LaTeXcommandExamAnswers.c_str());
         //  std::cout << "\n- PDF exam answers file generated\n\n";
      } else {
         std::cout << "\n- No PDF exam file generated\n\n";
         LOGE("No PDF exam file generated");
      }
   }
   catch (const std::bad_alloc &ba) {
      std::cerr << "\n\tERROR: OUT OF MEMORY " << ba.what() << std::endl;
      LOGE("ERROR: Out of memory " + ba.what());
   }
   catch (const std::exception &e) {
      std::cerr << "\n\tERROR: " << e.what() << std::endl;
      LOGE("ERROR: " + e.what());
   }
   catch (...) {
      std::cerr << "\n\tERROR: UNKNOWN EXCEPTION" << std::endl;
      LOGE("ERROR: UNKNOWN EXCEPTION");
   }

   LOGI("Bye... :-)");
   std::cout << "\nBye... :-) \n\n";

   return 0;
}

std::tuple<bfs::path> processCLI(int argc, char *argv[])
{
   bfs::path currentInitialDir(bfs::initial_path());
   bfs::path examScriptFileName;
   bpo::options_description descr("\n" APPNAME " v" VERSION);

   descr.add_options()("help,h", "show help message");
   descr.add_options()("version,v", "print version string");
   descr.add_options()("seed,s", bpo::value<long int>(),
                       "input seed for random generator");
   descr.add_options()("exam,e", bpo::value<std::string>(),
                       "input exam specification file name");
   descr.add_options()("debug,d", bpo::value<unsigned int>(),
                       "set logger in debug level mode");
   descr.add_options()("levelmin", bpo::value<unsigned int>(),
                       "set minimal level (not implemented)");
   descr.add_options()("levelmax", bpo::value<unsigned int>(),
                       "set maximal level (not implemented)");

   bpo::variables_map var_map;
   bpo::store(bpo::parse_command_line(argc, argv, descr), var_map);

   LOGI("Current dir: " + currentInitialDir.string());

   if (var_map.count("help")) {
      std::cout << descr << std::endl;
      exit(EXIT_SUCCESS); //===================================================>
   }

   if (var_map.count("version")) {
      std::cout << APPNAME " v" VERSION << std::endl;
      exit(EXIT_SUCCESS); //===================================================>
   }

   if (var_map.count("seed")) {
      setSeed(var_map["seed"].as<long int>());
   } else {
      setSeed(SEED_DEFAULT);
   }
   LOGI("seed = " + std::to_string(getSeed()));

   if (var_map.count("exam")) {
      examScriptFileName = var_map["exam"].as<std::string>();
      LOGI("Exam script = " + examScriptFileName.string());
   } else {
      std::cerr << "\n\tERROR: input exam specification file name missing\n"
                << descr << std::endl;
      LOGE("Exam script file name missing in command line");
      exit(EXIT_FAILURE); //===================================================>
   }

   if (var_map.count("debug")) {
      auto level{var_map["debug"].as<unsigned int>()};
      if (level < 1 or level > 3) {
         std::cerr << "\n\tERROR: debug level = " << level << " is wrong\n"
                   << std::endl;
         LOGE("Debug level not correct");
         exit(EXIT_FAILURE); //================================================>
      }
      Logger::instance().setLevel(level);
      Logger::instance().setDebugMode();
   }

   return std::tuple<bfs::path>(examScriptFileName);
}