//
// Created by Nathan Goller-Deitsch on 9/29/21.
//

#ifndef SYNTH_DRAW2D_H
#define SYNTH_DRAW2D_H

#include <boost/algorithm/string/join.hpp>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "Command.h"

namespace Kuka {

    class Draw2DCommand;
    class Draw2DCanvas;
    class Draw2DPoint;
    class Draw2DPath;

    class Draw2DCommand {
    public:
        virtual const Draw2DPoint getStartPoint() = 0;
        virtual const std::string compileKRL(Draw2DCanvas * canvas) = 0;
    };

    class Draw2DCanvas : public Command {
    public:
        Kuka::Frame origin;
        float width;
        float height;

        Draw2DCanvas(const Frame &origin, float width, float height);
        std::vector<std::unique_ptr<Draw2DCommand>> commands;
        const std::string compileKRL();
        Kuka::Draw2DPath* drawBoundaries();
        Kuka::Frame pointToFrame(Draw2DPoint input);
        Kuka::Frame penUp();
        Kuka::Frame penDown();
    };

    class Draw2DPoint {
    public:
        float x;
        float y;

        Draw2DPoint(float x, float y);
        float distanceTo(Draw2DPoint input);
    };

    class Draw2DPath : public Draw2DCommand {
    public:
        std::vector<Draw2DPoint> points;

        Draw2DPath(const std::vector<Draw2DPoint> &points);

        const Draw2DPoint getStartPoint() override;
        const std::string compileKRL(Draw2DCanvas * canvas) override;
    };
};  // namespace Kuka

#endif  // SYNTH_DRAW2D_H
