
#include <KRL/Group.h>
#include "Track.h"
#include "Note.h"

KRL::Frame Piano::Track::noteToFrame(Piano::Note input) const {
    if (input.getValue() > (this->keys - 1) || input.getValue() < 0) {
        throw std::invalid_argument("can't play outside the bounds of the piano");
    }

    // find quotient of input
    int inputKey = input.getValue();
    if (!(firstNote.getValue() == C)) {
        inputKey += (12 - firstNote.getValue());
    }

    int octaveIndex = inputKey / 12;
    KRL::Frame octaveOffset = KRL::Frame(origin.x, origin.y, {}, {}, {}, {}) +
                              KRL::Frame({}, -(octaveIndex * 7 * this->width), {}, {}, {},
                                         {});


    int keyIndex = inputKey % 12;
    switch (keyIndex) {
        case C:
            return octaveOffset;
        case C_SHARP:
            return octaveOffset + KRL::Frame(30, -(this->width * 0.5), {}, {}, {}, {});
        case D:
            return octaveOffset + KRL::Frame({}, -(this->width * 1), {}, {}, {}, {});
        case D_SHARP:
            return octaveOffset + KRL::Frame(30, -(this->width * 1.5), {}, {}, {}, {});
        case E:
            return octaveOffset + KRL::Frame({}, -(this->width * 2), {}, {}, {}, {});
        case F:
            return octaveOffset + KRL::Frame({}, -(this->width * 3), {}, {}, {}, {});
        case F_SHARP:
            return octaveOffset + KRL::Frame(30, -(this->width * 3.5), {}, {}, {}, {});
        case G:
            return octaveOffset + KRL::Frame({}, -(this->width * 4), {}, {}, {}, {});
        case G_SHARP:
            return octaveOffset + KRL::Frame(30, -(this->width * 4.5), {}, {}, {}, {});
        case A:
            return octaveOffset + KRL::Frame({}, -(this->width * 5), {}, {}, {}, {});
        case A_SHARP:
            return octaveOffset + KRL::Frame(30, -(this->width * 5.5), {}, {}, {}, {});
        case B:
            return octaveOffset + KRL::Frame({}, -(this->width * 6), {}, {}, {}, {});
    }
}

Piano::Track::Track(const KRL::Frame &origin, float width, int keys, Piano::Note firstNote) : origin(origin),
                                                                                              width(width),
                                                                                              keys(keys),
                                                                                              firstNote(firstNote) {
    if (!(origin.x && origin.y && origin.z && origin.a && origin.b && origin.c)) {
        throw std::invalid_argument("can't construct piano with incomplete frame");
    }
    if (keys <= 0) {
        throw std::invalid_argument("a piano must have at least one key");
    }
}

std::string Piano::Track::compileKRL() {
    KRL::Group group;
    group.commands.emplace_back(new KRL::PTP(origin + KRL::Frame({}, {}, 100, {}, {}, {})));

    while (!notes.empty()) {
        Piano::Note note = notes.front();
        KRL::Frame playheadOffset = {};
        if ((note.getValue() == C_SHARP) ||
            (note.getValue() == D_SHARP) ||
            (note.getValue() == F_SHARP) ||
            (note.getValue() == G_SHARP) ||
            (note.getValue() == A_SHARP)) {
            playheadOffset = KRL::Frame({}, {}, 5, {}, {}, {});
        }
        group.commands.emplace_back(new KRL::LIN(noteToFrame(note) + playheadUp() + playheadOffset));
        group.commands.emplace_back(new KRL::LIN(noteToFrame(note) + playheadDown() + playheadOffset));
        group.commands.emplace_back(new KRL::LIN(noteToFrame(note) + playheadUp() + playheadOffset));
        notes.erase(notes.begin());
    }

    return group.compileKRL();
}

KRL::Frame Piano::Track::playheadUp() {
    return KRL::Frame({}, {}, this->origin.z.value() + 20, {}, {}, {});
}

KRL::Frame Piano::Track::playheadDown() {
    return KRL::Frame({}, {}, this->origin.z.value(), {}, {}, {});
}

