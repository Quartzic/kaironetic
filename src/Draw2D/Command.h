
#ifndef SYNTH_COMMAND2_H
#define SYNTH_COMMAND2_H

#include "Point.h"
#include "Canvas.h"

using namespace Kaironetic::Draw2D;

namespace Kaironetic::Draw2D {
    class Canvas;

    /// \brief A structure that can be compiled to KRL with respect to a Canvas
    class Command {
    public:
        virtual Point getStartPoint() = 0;

        virtual Point getEndPoint() = 0;

        virtual std::string compileKRL(Canvas *canvas) = 0;
    };
}
#endif //SYNTH_COMMAND2_H
