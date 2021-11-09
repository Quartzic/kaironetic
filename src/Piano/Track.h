
#ifndef KAIRONETIC_TRACK_H
#define KAIRONETIC_TRACK_H

#include "KRL/Command.h"
#include "Note.h"

using namespace Kaironetic;

namespace Kaironetic::Piano {
    /// \example piano_example.cpp
    /// Plays "Yankee Doodle Dandy" on a Casio 44-key keyboard. WIP.

    /// \brief Represents a Piano and a set of Notes to be played
    class Track : public KRL::Command {
    public:
        /// A Frame that represents the center of the leftmost key.
        KRL::Frame origin;
        /// The width of each white key (in millimeters).
        float width;
        /// The total number of keys.
        int keys;
        /// The first note on the keyboard.
        Piano::Note firstNote;

        Track(const KRL::Frame &origin, float width, int keys, Piano::Note firstNote);

        /// An ordered collection of Notes.
        std::vector<Piano::Note> notes;

        /// @returns Returns a string representing this Track and each Piano::Note that it contains.
        std::string compileKRL() override;

        /// @brief Converts a given Note to a Frame that represents that position in the workspace.
        KRL::Frame noteToFrame(Piano::Note input) const;

        /// @returns Returns a Frame representing the playhead-up position.
        KRL::Frame playheadUp();

        /// @returns Returns a Frame representing the playhead-down position.
        KRL::Frame playheadDown();
    };
};


#endif //KAIRONETIC_TRACK_H
