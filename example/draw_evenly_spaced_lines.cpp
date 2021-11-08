#include <filesystem>  // C++17
#include <fstream>
#include <iostream>
#include <Draw2D/Canvas.h>

#include "KRL/Command.h"
#include "KRL/Group.h"

#define LINE_COUNT 9

using namespace Kaironetic;
namespace fs = std::filesystem;

int main(int argc, char **argv) {

    // initialize the kuka program
    std::fstream outputFile;
    KRL::Group program;
    program.commands.emplace_back(new KRL::STARTWRAPPER());

    // set up the canvas
    Draw2D::Canvas *canvas = new Draw2D::Canvas(KRL::Frame(215, -130, 405, 128, 31, 178), 150, 250);;

    // draw evenly spaced paths (lines) on the canvas
    for (int i = 1; i < LINE_COUNT; i++) {
        canvas->commands.emplace_back(
                new Draw2D::Path({Draw2D::Point(0, (canvas->height / LINE_COUNT) * i),
                                  Draw2D::Point(canvas->width, (canvas->height / LINE_COUNT) * i)})
        );
    }

    // add the canvas to the program
    program.commands.emplace_back(canvas);

    // close the program, write to file
    program.commands.emplace_back(new KRL::ENDWRAPPER());
    outputFile.open("draw_evenly_spaced_lines.src", std::fstream::out);
    outputFile << program.compileKRL();
    outputFile.close();

    return 0;
}