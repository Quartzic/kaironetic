#include <filesystem>  // C++17
#include <fstream>
#include <iostream>
#include <Draw2D/Canvas.h>
#include <Piano/Track.h>

#include "KRL/Command.h"
#include "KRL/Group.h"
#include "Piano/Note.h"

using namespace Kaironetic;
namespace fs = std::filesystem;

int main(int argc, char **argv) {

    // initialize the kuka program
    std::fstream outputFile;
    KRL::Group program;
    program.commands.emplace_back(new KRL::STARTWRAPPER());

    // set up the track
    Piano::Track *track = new Piano::Track(KRL::Frame(173.87, 465.88, 369.25, 176.75, 31.36, 178.20), 20, 44,
                                           Piano::Note(F));;

    std::vector<int> notes = {C, C_SHARP, D, D_SHARP, E, F, F_SHARP, G, G_SHARP, A};

    for (int i = 0; i < notes.size(); i++) {
        track->notes.emplace_back(Piano::Note(0, notes[i]));
    }
    // add the track to the program
    program.commands.emplace_back(track);

    // close the program, write to file
    program.commands.emplace_back(new KRL::ENDWRAPPER());
    outputFile.open("piano_example.src", std::fstream::out);
    outputFile << program.compileKRL();
    outputFile.close();

    return 0;
}