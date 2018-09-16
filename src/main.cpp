#include "AppInfo.h"
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
using namespace std;

int main(int argc, char *argv[])
{
   try {
      bfs::path currentInitialDir(bfs::initial_path());
      bfs::path MCTspecFileName;
      bpo::options_description descr(APPNAME " - Test Generator - ");
      descr.add_options()("help,h", "produce help message")(
         "version,v", "print version string")("specification,s",
                                              bpo::value<string>(),
                                              "input specification file")(
         "hct,t", "execute hard coded specification");
      bpo::variables_map var_map;
      bpo::store(bpo::parse_command_line(argc, argv, descr), var_map);

      if (var_map.count("help")) {
         clog << descr << endl;
         return 1;
      }
      if (var_map.count("version")) {
         clog << VERSION << endl;
         return 1;
      }
      if (var_map.count("specification")) {
         MCTspecFileName = var_map["specification"].as<string>();
      } else {
         clog << "\nERROR: input specification file name missing\n\n";
         clog << descr << endl;
         return 1;
      }

      cout << "- " << APPNAME << " v" << VERSION << " started in "
           << currentInitialDir << endl
           << endl;

      const bfs::path LaTeXoutputDir("MCTlatex");
      const bfs::path LaTeXgeneratedFileName(LaTeXoutputDir /
                                             "MCTgenerated.tex");
      const bfs::path LaTeXdocFileName("MCTdoc.tex");
      const string LaTeXcommand(
         "pdflatex -enable-write18 \"-output-directory=" +
         LaTeXoutputDir.string() + "\" " +
         (LaTeXoutputDir / LaTeXdocFileName).string());

      bfs::ofstream LaTeXgeneratedFile(LaTeXgeneratedFileName);
      if (!LaTeXgeneratedFile) {
         cerr << "%%$##^((*& " << LaTeXgeneratedFileName << " not opened"
              << endl;
         cin.get();
         exit(1);
      }
      if (var_map.count("hct")) {
         //   MCTgenTests::test1(LaTeXgeneratedFile);
         //   MCTgenTests::testAll(LaTeXgeneratedFile);
      }
      bfs::ifstream MCTspecFile(MCTspecFileName);
      if (!MCTspecFile) {
         cerr << "*&^*&^%^&% MCTspecFile: " << MCTspecFileName
              << " not opened" << endl;
         cin.get();
         exit(1);
      }

      // Start MC test construction scripted
      // Reader reader(MCTspecFile);
      // reader.read();
      // vector<std::shared_ptr<GenMCTs>> scriptedTests(reader.parse());

      // if (!scriptedTests.empty())
      // {
      //   cout << "- Generating scripted MCT's" << endl;

      //   for_each(scriptedTests.begin(), scriptedTests.end(),
      //   [&LaTeXgeneratedFile](std::shared_ptr<GenMCTs>& st) {
      //   st->generate(LaTeXgeneratedFile); } );
      //   LaTeXgeneratedFile.close();

      //   cout << "- LaTeX file generated\n";
      //   cout << "- Started PDF file generation\n";
      //   // Generate DVI file
      //   system(LaTeXcommand.c_str());
      //   cout << "\n- PDF file generated\n\n";
      // }
      // else
      // {
      //   cout << "\n- No PDF file generated\n\n";
      // }
   } catch (const std::bad_alloc &ba) {
      clog << "\n\t OUT OF MEMORY " << ba.what() << endl;
   } catch (const std::exception &e) {
      clog << "\n\t" << e.what() << endl;
   } catch (...) {
      clog << "\n\tUNKNOWN EXCEPTION" << endl;
   }

   cout << "\nBye... :-) \n\n";
   cin.get();

   return 0;
}