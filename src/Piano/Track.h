
#ifndef KAIRONETIC_TRACK_H
#define KAIRONETIC_TRACK_H

#import "KRL/Command.h"
#include "Note.h"

using namespace Kaironetic;

namespace Piano {
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

        std::__1::vector<Piano::Note> notes;

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
