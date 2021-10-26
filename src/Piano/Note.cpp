
#include <string>
#include <KRL/Group.h>
#include "Note.h"
#include "Track.h"

Piano::Note::Note(int value) : value(value) {}

Piano::Note::Note(int octave, int note) {
    // add an octave offset
    this->value = (octave * 12) + note;
}

int Piano::Note::getValue() const {
    return value;
}

void Piano::Note::setValue(int value) {
    Note::value = value;
}