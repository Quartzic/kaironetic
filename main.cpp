#include <boost/program_options.hpp>
#include <filesystem>  // C++17
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "kuka/Command.h"
#include "kuka/Draw2D.h"
#include "kuka/Group.h"

#include "cascade_model.cpp"

using namespace boost::program_options;
using namespace cv;
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
  const std::string outputPath = vm["output"].as<std::string>();
  bool overwrite = vm["overwrite"].as<bool>();

  if(!overwrite) {
    // Ensure the output file doesn't already exist
    if (std::filesystem::exists(outputPath)) {
      throw std::invalid_argument(
          outputPath + " already exists, delete it or set --overwrite");
    }
  }
    // initialize the kaironetic program
    std::fstream outputFile;
    Kaironetic::Group myProgram;
    myProgram.commands.emplace_back(new Kaironetic::STARTWRAPPER());

    Kaironetic::Draw2DCanvas *myCanvas = new Kaironetic::Draw2DCanvas(Kaironetic::Frame(215, -130, 405, 128, 31, 178), 150, 250);

    myCanvas->commands.emplace_back(myCanvas->drawBoundaries());

    for(int i = 1; i < 20; i++){
                myCanvas->commands.emplace_back(
                        new Kuka::Draw2DPath({Kuka::Draw2DPoint(0, 10*i), Kuka::Draw2DPoint(myCanvas->width, 10*i)})
                );
    }

    myProgram.commands.emplace_back(myCanvas);

    // close the program
  myProgram.commands.emplace_back(new Kaironetic::ENDWRAPPER());
   outputFile.open(outputPath, std::fstream::out);
   outputFile << myProgram.compileKRL();
   outputFile.close();

  return 0;
}