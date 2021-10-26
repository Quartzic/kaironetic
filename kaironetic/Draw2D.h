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
#include <memory>

#include "Command.h"

namespace Kaironetic {

    class Draw2DCommand;

    class Draw2DCanvas;

    class Draw2DPoint;

    class Draw2DPath;

    class Draw2DCommand {
    public:
        virtual const Draw2DPoint getStartPoint() = 0;

        virtual const Draw2DPoint getEndPoint() = 0;

        virtual const std::string compileKRL(Draw2DCanvas *canvas) = 0;
    };

    /// @brief Represents a two-dimensional canvas in the workspace, like a piece of paper.

    class Draw2DCanvas : public Command {
    public:
        Kaironetic::Frame origin;
        float width;
        float height;

        /// @param origin A frame that represents a pen placed down at the origin of the canvas.
        /// @param width The width of the canvas (in millimeters).
        /// @param width The height of the canvas (in millimeters).
        Draw2DCanvas(const Frame &origin, float width, float height);

        std::vector<std::unique_ptr<Draw2DCommand>> commands;


        const std::string compileKRL();

        /// @returns Returns a Draw2DPath representing the boundaries of the canvas.
        Kaironetic::Draw2DPath *drawBoundaries();

        /// @brief Converts a given Draw2DPoint to a Frame that represents that position in the workspace.
        Kaironetic::Frame pointToFrame(Draw2DPoint input);

        /// @returns Returns a Frame representing the pen-up position.
        Kaironetic::Frame penUp();

        /// @returns Returns a Frame representing the pen-down position.
        Kaironetic::Frame penDown();
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

        const Draw2DPoint getEndPoint() override;

        const std::string compileKRL(Draw2DCanvas *canvas) override;
    };

    class Draw2DSpline : public Draw2DCommand {
    public:
        std::vector<Draw2DPoint> points;

        Draw2DSpline(const std::vector<Draw2DPoint> &points);

        const Draw2DPoint getStartPoint() override;

        const Draw2DPoint getEndPoint() override;

        const std::string compileKRL(Draw2DCanvas *canvas) override;
    };
};  // namespace Kuka

#endif  // SYNTH_DRAW2D_H
