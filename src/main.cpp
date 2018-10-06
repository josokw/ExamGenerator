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
#include "hcExam/hcExamDummy.h"

#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/program_options.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace bpo = boost::program_options;
namespace bfs = boost::filesystem;

int main(int argc, char *argv[])
{
   try {
      LOGI(APPNAME " v" VERSION " started");

      bfs::path currentInitialDir(bfs::initial_path());
      bfs::path ExamScriptFileName;
      bpo::options_description descr("\n" APPNAME " v" VERSION);

      descr.add_options()("help,h", "show help message");
      descr.add_options()("version,v", "print version string");
      descr.add_options()("seed,s", bpo::value<long int>(),
                          "input seed for random generator");
      descr.add_options()("exam,e", bpo::value<std::string>(),
                          "input exam specification file name");
      descr.add_options()("debug,d", "set logger in debug mode");
      descr.add_options()("hce,c", "execute hard coded exam");

      bpo::variables_map var_map;
      bpo::store(bpo::parse_command_line(argc, argv, descr), var_map);

      LOGI("Current dir: " + currentInitialDir.string());

      if (var_map.count("help")) {
         std::clog << descr << std::endl;
         return 0;
      }
      if (var_map.count("version")) {
         std::clog << APPNAME " v" VERSION << std::endl;
         return 0;
      }
      if (var_map.count("seed")) {
         auto seed = var_map["seed"].as<long int>();
         LOGI("seed = " + std::to_string(seed));
      }
      if (var_map.count("exam")) {
         ExamScriptFileName = var_map["exam"].as<std::string>();
      } else {
         std::cerr << "\n\tERROR: input exam specification file name missing\n"
                   << descr << std::endl;
         LOGE("Exam script file name missing in command line");
         exit(EXIT_FAILURE);
      }
      if (var_map.count("debug")) {
         //  logger.setDebugMode();
      }

      std::cout << "- " << APPNAME << " v" << VERSION << " started in "
                << currentInitialDir << std::endl;

      const bfs::path LaTeXoutputDir(".");
      const bfs::path LaTeXgeneratedFileName(LaTeXoutputDir /
                                             "generatedExam.tex");
      LOGI("Generated LaTex file: " +
           (LaTeXoutputDir / "generatedExam.tex").string());

      const bfs::path LaTeXdocFileName(EXAM_LATEX_FILENAME);
      const std::string LaTeXcommand(
         "pdflatex -enable-write18 \"-output-directory=" +
         LaTeXoutputDir.string() + "\" " +
         (LaTeXoutputDir / LaTeXdocFileName).string());

      bfs::ofstream LaTeXgeneratedFile(LaTeXgeneratedFileName);
      if (!LaTeXgeneratedFile) {
         std::cerr << "\n\tERROR: " << LaTeXgeneratedFileName
                   << " not opened\n\n";
         exit(EXIT_FAILURE);
      }

      bfs::ifstream ExamScriptFile(ExamScriptFileName);
      if (!ExamScriptFile) {
         LOGE("Exam script file '" + ExamScriptFileName.string() +
              "' does not exists");
         std::cerr << "\n\tERROR: exam script file '"
                   << ExamScriptFileName.string() << "' does not exists\n\n";
         exit(EXIT_FAILURE);
      }

      if (var_map.count("hce")) {
         LOGI("Hard coded exam");
         hcExamDummy(LaTeXgeneratedFile);
      }

      // Start generating exam based on script
      LOGI("Start reading exam script: " + ExamScriptFileName.string());
      Reader reader(ExamScriptFile);
      reader.read();
      std::vector<std::shared_ptr<GenExams>> scriptedTests(reader.parse());

      if (!scriptedTests.empty()) {
         std::cout << "- Generating scripted exams" << std::endl;

         LOGI("Start generating LaTeX file: " +
              LaTeXgeneratedFileName.string());
         for_each(scriptedTests.begin(), scriptedTests.end(),
                  [&LaTeXgeneratedFile](std::shared_ptr<GenExams> &st) {
                     st->generate(LaTeXgeneratedFile);
                  });

         LaTeXgeneratedFile.close();
         LOGI("Generated LaTeX file: " + LaTeXgeneratedFileName.string());

         std::cout << "- LaTeX file generated\n";
         std::cout << "- Started PDF exam file generation\n";
         LOGI("LaTeX to pdf command: " + LaTeXcommand);
         // Generate DVI file
         system(LaTeXcommand.c_str());
         std::cout << "\n- PDF exam file generated\n\n";
      } else {
         std::cout << "\n- No PDF exam file generated\n\n";
      }
   }
   catch (const std::bad_alloc &ba) {
      std::cerr << "\n\tERROR: OUT OF MEMORY " << ba.what() << std::endl;
      LOGE("ERROR: Out of memory " + ba.what());
   }
   catch (const std::exception &e) {
      std::cerr << "\n\tERROR: " << e.what() << std::endl;
      LOGE("ERROR: Out of memory " + e.what());
   }
   catch (...) {
      std::cerr << "\n\tERROR: UNKNOWN EXCEPTION" << std::endl;
      LOGE("ERROR: UNKNOWN EXCEPTION");
   }

   LOGI("Bye... :-)");
   std::cout << "\nBye... :-) \n\n";

   return 0;
}