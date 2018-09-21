#include "AppInfo.h"
#include "Log.h"
#include "RandomProfile.h"
#include "GenNull.h"

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
//#include "GenMCTs.h"
//#include "MCTgenTests.h"
//#include "Reader.h"

namespace bpo = boost::program_options;
namespace bfs = boost::filesystem;

int main(int argc, char *argv[])
{
   try {
      LOGI(APPNAME " v" VERSION " started");

      bfs::path currentInitialDir(bfs::initial_path());
      bfs::path MCTspecFileName;
      bpo::options_description descr(APPNAME " v" VERSION);

      descr.add_options()("help,h", "show help message");
      descr.add_options()("version,v", "print version string");
      descr.add_options()("seed,s", bpo::value<long int>(),
                          "input seed random generator");
      descr.add_options()("exam,e", bpo::value<std::string>(),
                          "input exam specification file");
      descr.add_options()("hct,t", "execute hard coded specification");

      bpo::variables_map var_map;
      bpo::store(bpo::parse_command_line(argc, argv, descr), var_map);

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
         MCTspecFileName = var_map["exam"].as<std::string>();
      } else {
        //  std::cerr << "\n\tERROR: input specification file name missing\n\n"
        //            << descr << std::endl;
        //  return 1;
      }

      std::cout << "- " << APPNAME << " v" << VERSION << " started in "
                << currentInitialDir << std::endl;

      const bfs::path LaTeXoutputDir("MCTlatex");
      const bfs::path LaTeXgeneratedFileName(LaTeXoutputDir /
                                             "MCTgenerated.tex");
      const bfs::path LaTeXdocFileName("MCTdoc.tex");
      const std::string LaTeXcommand(
         "pdflatex -enable-write18 \"-output-directory=" +
         LaTeXoutputDir.string() + "\" " +
         (LaTeXoutputDir / LaTeXdocFileName).string());

      bfs::ofstream LaTeXgeneratedFile(LaTeXgeneratedFileName);
      //   if (!LaTeXgeneratedFile) {
      //      std::cerr << "\n\tERROR: " << LaTeXgeneratedFileName
      //                << " not opened\n\n";
      //      exit(1);
      //   }
      if (var_map.count("hct")) {
         //   MCTgenTests::test1(LaTeXgeneratedFile);
         //   MCTgenTests::testAll(LaTeXgeneratedFile);
      }
      bfs::ifstream MCTspecFile(MCTspecFileName);
      //   if (!MCTspecFile) {
      //      std::cerr << "ERROR: MCTspecFile " << MCTspecFileName
      //                << " not opened\n\n";
      //      std::cin.get();
      //      exit(1);
      //   }

      Random::range_t rng{2, 6};
      RandomProfile rf;

      rf.generate(rng);
      auto r = rf.getProfile();
      for (auto i : r) {
         std::cout << i << std::endl;
      }

      GenNULL genNull;
      std::cout << genNull << std::endl;

      // Start MC test construction scripted
      // Reader reader(MCTspecFile);
      // reader.read();
      // vector<std::shared_ptr<GenMCTs>> scriptedTests(reader.parse());

      // if (!scriptedTests.empty())
      // {
      //   std::cout << "- Generating scripted MCT's" << std::endl;

      //   for_each(scriptedTests.begin(), scriptedTests.end(),
      //   [&LaTeXgeneratedFile](std::shared_ptr<GenMCTs>& st) {
      //   st->generate(LaTeXgeneratedFile); } );
      //   LaTeXgeneratedFile.close();

      //   std::cout << "- LaTeX file generated\n";
      //   std::cout << "- Started PDF file generation\n";
      //   // Generate DVI file
      //   system(LaTeXcommand.c_str());
      //   std::cout << "\n- PDF file generated\n\n";
      // }
      // else
      // {
      //   std::cout << "\n- No PDF file generated\n\n";
      // }
   }
   catch (const std::bad_alloc &ba) {
      std::cerr << "\n\tOUT OF MEMORY " << ba.what() << std::endl;
   }
   catch (const std::exception &e) {
      std::cerr << "\n\t" << e.what() << std::endl;
   }
   catch (...) {
      std::cerr << "\n\tUNKNOWN EXCEPTION" << std::endl;
   }

   std::cout << "\nBye... :-) \n\n";
   //    std::cin.get();

   return 0;
}