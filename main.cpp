#include <boost/program_options.hpp>
#include <filesystem>  // C++17
#include <fstream>
#include <iostream>

#include "kuka/Command.h"
#include "kuka/Group.h"

using namespace boost::program_options;

namespace po = boost::program_options;
namespace fs = std::filesystem;

int getRand(int min, int max){
  // inclusive of min, exclusive of max
    return((rand() % (max - min)) + min);
}
int main(int argc, char **argv) {
  std::vector<std::string> argList(argv, argv + argc);
  po::variables_map vm;

  // Get options
  po::options_description desc("Options for synth");
  desc.add_options()("help", "produce help message")
      ("input", po::value<std::string>(), "input file")
      ("output", po::value<std::string>()->required()->default_value("synth_out.src"),"output file")
      ("overwrite", po::bool_switch()->default_value(false), "overwrite existing output files");
  po::store(po::parse_command_line(argc, argv, desc), vm);

  // Return help message
  if (vm.count("help") || argc == 1) {
    std::cout << desc << std::endl;
    return 1;
  }

  // Raise errors about incorrect options
  po::notify(vm);

  // Cast variables from  variable map
  const std::string outputFileName = vm["output"].as<std::string>();
  bool overwrite = vm["overwrite"].as<bool>();

  // Error if input path is not a file
  // if (!fs::is_regular_file(inputPath)) {
    // throw std::invalid_argument(inputPath + " is not a file");
  // }

  if(!overwrite) {
    // Ensure the output file doesn't already exist
    if (std::filesystem::exists(outputFileName)) {
      throw std::invalid_argument(outputFileName + " already exists, delete it or set --overwrite");
    }
  }

    std::fstream outputFile;

    // example
   Kuka::Group myProgram;

   myProgram.commands.emplace_back(new Kuka::STARTWRAPPER());
   myProgram.commands.emplace_back(new Kuka::PTP(Kuka::Frame(350, -250, 425, 128, 31, 178)));

  for (int i = 1; i < 10; i++) {
    myProgram.commands.emplace_back(new Kuka::Draw2DSquare(300-(5*i), -250+(5*i), (i*10), (i*10)));
  }

   myProgram.commands.emplace_back(new Kuka::ENDWRAPPER());
   outputFile.open(outputFileName, std::fstream::out);
   outputFile << myProgram.compileKRL();
   outputFile.close();
  return 0;
}