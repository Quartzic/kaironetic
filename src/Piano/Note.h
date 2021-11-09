
#ifndef KAIRONETIC_NOTE_H
#define KAIRONETIC_NOTE_H


enum NOTE_INDEX {
    C = 0,
    C_SHARP = 1,
    D = 2,
    D_SHARP = 3,
    E = 4,
    F = 5,
    F_SHARP = 6,
    G = 7,
    G_SHARP = 8,
    A = 9,
    A_SHARP = 10,
    B = 11
};

namespace Kaironetic::Piano {

    class Note {
    public:
        Note(int value);

        Note(int octave, int key);

        int getValue() const;

        void setValue(int value);

    private:
        int value;
    };
};


#endif //KAIRONETIC_NOTE_H
