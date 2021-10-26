#include <filesystem>  // C++17
#include <fstream>
#include <iostream>
#include <Draw2D/Canvas.h>
#include "KRL/Command.h"
#include "KRL/Group.h"

using namespace Kaironetic;
namespace fs = std::filesystem;

int main(int argc, char **argv) {

    // initialize the kuka program
    std::fstream outputFile;
    KRL::Group program;
    program.commands.emplace_back(new KRL::STARTWRAPPER());

    // set up the canvas
    Draw2D::Canvas *canvas = new Draw2D::Canvas(KRL::Frame(215, -130, 405, 128, 31, 178), 150, 250);;
    canvas->commands.emplace_back(canvas->drawBoundaries());

    canvas->commands.emplace_back(drawRectangle(Draw2D::Point(7.5, 7), 14.7, 69.8));
    canvas->commands.emplace_back(drawRectangle(Draw2D::Point(31.5, 7), 14.7, 47.5));
    canvas->commands.emplace_back(drawRectangle(Draw2D::Point(55.4, 7), 14.7, 69.8));
    canvas->commands.emplace_back(drawRectangle(Draw2D::Point(79.4, 7), 14.7, 13.9));
    canvas->commands.emplace_back(drawRectangle(Draw2D::Point(79.4, 29.3), 14.7, 47.5));
    canvas->commands.emplace_back(drawRectangle(Draw2D::Point(103.8, 7), 38.7, 13.9));
    canvas->commands.emplace_back(drawRectangle(Draw2D::Point(103.8, 29.3), 14.7, 47.5));

    // add the canvas to the program
    program.commands.emplace_back(canvas);

    // close the program, write to file
    program.commands.emplace_back(new KRL::ENDWRAPPER());
    outputFile.open("draw_mit_logo.src", std::fstream::out);
    outputFile << program.compileKRL();
    outputFile.close();

    return 0;
}