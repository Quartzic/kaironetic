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
  Mat inputImageGray;

  // Error if image is empty
  if (inputImage.empty()) {
    std::cerr << inputPath << " couldn't be read" << std::endl;
    return -1;
  }


  // resize input image, convert to single color, write out for debugging purposes
  cvtColor(inputImage, inputImageGray, COLOR_BGR2GRAY);
  threshold(inputImageGray, inputImageGray, 10, 255, THRESH_BINARY);
  imwrite("debug.jpg", inputImage);
  std::vector<std::vector<Point>> contours;
  std::vector<Vec4i> hierarchy;
  findContours(inputImageGray, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
// draw contours on the original image
  Mat image_copy = inputImage.clone();
  drawContours(image_copy, contours, -1, Scalar(0, 255, 0), 2);
    // example
   Kuka::Group myProgram;

   myProgram.commands.emplace_back(new Kuka::STARTWRAPPER());

   // initialize pen
   myProgram.commands.emplace_back(new Kuka::PTP(Kuka::Frame(350, -250, 425, 128, 31, 178)));

//  for (int i = 0; i < contours.size(); i++) {
//    Kuka::Draw2DPath *path = new Kuka::Draw2DPath({});
//    std::vector<Point> approxContour;
//    approxPolyDP(contours[i], approxContour, (0.01 * arcLength(contours[i], true)), true);
//    approxContour.emplace_back(approxContour[0]);
//     for (int j = 0; j < approxContour.size(); j++) {
//       path->points.emplace_back(Kuka::Draw2DPoint(
//           (250 + (0.25 * approxContour[j].x)), (-200 - (0.25 * approxContour[j].y))));
//     }
//     std::cout << "wrote polygon with " << approxContour.size() << " points" << std::endl;
//     myProgram.commands.emplace_back(path);
//   }

   myProgram.commands.emplace_back(new Kuka::Draw2DPath(
       {
            Kuka::Draw2DPoint(255, -190),
            Kuka::Draw2DPoint(255, -200),
       }
       ));
  myProgram.commands.emplace_back(new Kuka::Draw2DPath(
      {
           Kuka::Draw2DPoint(265, -190),
           Kuka::Draw2DPoint(265, -200),
      }
  ));
   myProgram.commands.emplace_back(new Kuka::Draw2DSpline(
       {
          Kuka::Draw2DPoint(250, -200),
          Kuka::Draw2DPoint(260, -215),
          Kuka::Draw2DPoint(270, -200),
       }
   ));

  Kuka::Draw2DSpline *spline = new Kuka::Draw2DSpline({});

  float x = 0;
  float y = 0;
  float angle = 0.0f;

// Space between the spirals
  int a = 2, b = 2;

  for (int i = 0; i < 50; i++)
  {
    angle = 0.1 * i;
    x = 300 + (a + b * angle) * cos(angle);
    y = -200 + (a + b * angle) * sin(angle);

    spline->points.emplace_back(Kuka::Draw2DPoint(x, y));
  }
  myProgram.commands.emplace_back(spline);
  myProgram.commands.emplace_back(new Kuka::ENDWRAPPER());
   outputFile.open(outputPath, std::fstream::out);
   outputFile << myProgram.compileKRL();
   outputFile.close();

  return 0;
}