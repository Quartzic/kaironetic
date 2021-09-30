#include <boost/program_options.hpp>
#include <filesystem>  // C++17
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "kuka/Command.h"
#include "kuka/Draw2D.h"
#include "kuka/Group.h"

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
      ("input", po::value<std::string>()->required(), "input file (raster image)")
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
  const std::string inputPath = vm["input"].as<std::string>();
  const std::string outputPath = vm["output"].as<std::string>();
  bool overwrite = vm["overwrite"].as<bool>();

  // Error if input path is not a file
  if (!fs::is_regular_file(inputPath)) {
     throw std::invalid_argument(inputPath + " is not a file");
  }

  if(!overwrite) {
    // Ensure the output file doesn't already exist
    if (std::filesystem::exists(outputPath)) {
      throw std::invalid_argument(
          outputPath + " already exists, delete it or set --overwrite");
    }
  }


  std::fstream outputFile;

  Mat inputImage = imread(inputPath);

  // Error if image is empty
  if (inputImage.empty()) {
    std::cerr << inputPath << " couldn't be read" << std::endl;
    return -1;
  }


  // resize input image, convert to single color, write out for debugging purposes
  resize(inputImage, inputImage, Size(), 0.25, 0.25, INTER_LANCZOS4);
  cvtColor(inputImage, inputImage, COLOR_BGR2GRAY);
  threshold(inputImage, inputImage, 10, 255, THRESH_BINARY);
  imwrite("debug.jpg", inputImage);


    // example
   Kuka::Group myProgram;

   myProgram.commands.emplace_back(new Kuka::STARTWRAPPER());

   // initialize pen
   myProgram.commands.emplace_back(new Kuka::PTP(Kuka::Frame(350, -250, 425, 128, 31, 178)));


   // add commands to draw each line based on contiguous segments of white pixels in each row

  for (int i = 0; i<inputImage.rows; i++)
  {
    int lineStart = -1;
    int lineEnd = -1;
    if(i % 2 == 0){
      for (int j = 0; j<inputImage.cols; j++)
      {
        if(inputImage.at<uchar>(i, j) == 255){
          if(lineStart == -1){
            lineStart = j;
          }
          lineEnd = j;
        }else{
          if(lineStart != -1){
            myProgram.commands.emplace_back(new Kuka::Draw2DPath({Kuka::Draw2DPoint((300 + (2 * i)), (-200 - (lineStart * 2))), Kuka::Draw2DPoint((300 + (2 * i)), (-200 - (lineEnd * 2)))}));
            lineStart = -1;
            lineEnd = -1;
          }
        }
      }
    }else{
      for (int j = inputImage.cols; j > 0; j--)
      {
        if(inputImage.at<uchar>(i, j) == 255){
          if(lineStart == -1){
            lineStart = j;
          }
          lineEnd = j;
        }else{
          if(lineStart != -1){
            myProgram.commands.emplace_back(new Kuka::Draw2DPath({Kuka::Draw2DPoint((300 + (2 * i)), (-200 - (lineStart * 2))), Kuka::Draw2DPoint((300 + (2 * i)), (-200 - (lineEnd * 2)))}));
            lineStart = -1;
            lineEnd = -1;
          }
        }
      }
    }
    std::cout << std::endl;
  }

  myProgram.commands.emplace_back(new Kuka::ENDWRAPPER());
   outputFile.open(outputPath, std::fstream::out);
   outputFile << myProgram.compileKRL();
   outputFile.close();
  return 0;
}