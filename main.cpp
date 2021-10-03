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

    // open the first webcam plugged in the computer
    cv::VideoCapture camera(0);
    if (!camera.isOpened()) {
        std::cerr << "ERROR: Could not open camera" << std::endl;
        return 1;
    }

    // create a window to display the images from the webcam
    cv::namedWindow("Webcam", cv::WINDOW_AUTOSIZE);

    // initialize the kuka program
    std::fstream outputFile;
    Kuka::Group myProgram;
    myProgram.commands.emplace_back(new Kuka::STARTWRAPPER());

    // initialize pen
    myProgram.commands.emplace_back(new Kuka::PTP(Kuka::Frame(350, -250, 425, 128, 31, 178)));

    // setup opencv variables
    cv::Mat rawFrame;
    cv::Mat frame;
    cv::Mat frame_grey;
    cv::Mat frame_blurred;
    cv::Mat frame_canny;
    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hierarchy;
    int contourTarget = 200;
    int threshold1 = 100;
    int threshold2 = 200;

    while (1) {
        // capture the next frame from the webcam
        camera >> rawFrame;

        // find contours (non-smoothed)
        cv::resize(rawFrame, frame, Size(320, 180), INTER_LINEAR);
        cv::GaussianBlur(frame, frame_blurred, Size(5, 5), 0);
        cv::Canny(frame, frame_canny, threshold1, threshold2);
        cv::findContours(frame_canny, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

        // draw contours on image
        Mat final = frame_blurred.clone();
        drawContours(final, contours, -1, Scalar(0, 255, 0), 1);
        cv::resize(final, final, Size(1280, 720), INTER_LINEAR);


        // draw UI elements

        cv::putText(final, //target image
                    "Synth (Q to quit)",
                    cv::Point(10, 10), //top-left position
                    cv::FONT_HERSHEY_PLAIN,
                    1.0,
                    CV_RGB(255, 0, 0), //font color
                    1);

        cv::putText(final, //target image
                    "Contour Target (W to increase, S to decrease): " + std::to_string(contourTarget), //text
                    cv::Point(10, 20),
                    cv::FONT_HERSHEY_PLAIN,
                    1.0,
                    CV_RGB(255, 0, 0), //font color
                    1);

        cv::putText(final, //target image
                    "Contours: " + std::to_string(contours.size()), //text
                    cv::Point(10, 40),
                    cv::FONT_HERSHEY_PLAIN,
                    1.0,
                    CV_RGB(255, 0, 0), //font color
                    1);

        // show the image on the window
        cv::imshow("Webcam", final);

        // adjust threshold to meet contour target
        if(contours.size() > contourTarget){
            threshold2 += 1;
        }
        if(contours.size() < contourTarget){
            threshold2 -= 1;
        }


        // await keypress
        char keyPressed = cv::waitKey(10);
        if (keyPressed == 'w'){
            contourTarget += 5;
        }else if(keyPressed == 's'){
            contourTarget -= 5;
        }

        if(keyPressed == 'q'){
            break;
        }
        if(keyPressed == ' '){
            std::vector<std::vector<Point>> smoothed;
              for (int i = 0; i < contours.size(); i++) {
                  // setup a new kuka 2D spline path
                Kuka::Draw2DSpline *path = new Kuka::Draw2DSpline({});

                // smooth the contour
                std::vector<Point> approxContour;
                approxPolyDP(contours[i], approxContour, (0.01 * arcLength(contours[i], true)), true);
                // put the contour in the smoothed vector for later display
                smoothed.emplace_back(approxContour);

                  // for each point in the contour, add it to the 2d spline path
                 for (int j = 0; j < approxContour.size(); j++) {
                   path->points.emplace_back(Kuka::Draw2DPoint(
                       (250 + (0.25 * approxContour[j].x)), (-200 - (0.25 * approxContour[j].y))));
                 }

                 // write it to the main program
                 std::cout << "wrote spline with " << approxContour.size() << " points" << std::endl;
                 myProgram.commands.emplace_back(path);
               }

              // display the smoothed contours
              cv::Mat smoothedContourPreview = Mat::zeros(frame.size(), CV_8UC1);
              drawContours(smoothedContourPreview, smoothed, -1, Scalar(255, 0, 0));
              imshow("Final Preview", smoothedContourPreview);
              cv::waitKey(0);
              break;
        }
    }

    // close the program
  myProgram.commands.emplace_back(new Kuka::ENDWRAPPER());
   outputFile.open(outputPath, std::fstream::out);
   outputFile << myProgram.compileKRL();
   outputFile.close();

  return 0;
}