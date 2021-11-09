#ifndef SYNTH_CANVAS_H
#define SYNTH_CANVAS_H

#include "Path.h"
#include "Point.h"
#include "../KRL/Command.h"
#include "../KRL/Frame.h"
#include <boost/algorithm/string/join.hpp>
#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <memory>

namespace Kaironetic::Draw2D {
    class Command;

    class Path;

    /// \example draw_evenly_spaced_lines.cpp
    /// Draws evenly spaced lines using a Canvas.

    /// \example draw_mit_logo.cpp
    /// Draws the MIT logo using a Canvas.
    /// Kaironetic is not sponsored by or affiliated with the Massachusetts Institute of Technology.

    /// \brief Represents a 2D canvas and a set of shapes to be drawn
    ///
    /// Canvas provides the appropriate facilities to draw on a plane; for example, a piece of paper.
    /// It will store a set of Draw2DCommands and sort their draw order to decrease unnecessary travel; therefore, do not rely on a specific ordering.
    /// If you attempt to draw outside of the defined boundaries of the Canvas, an exception will be thrown.

    class Canvas : public KRL::Command {
    public:
        /// A Frame that represents the origin (top left) of the canvas.
        KRL::Frame origin;
        /// The width of the canvas (in millimeters).
        float width;
        /// The height of the canvas (in millimeters).
        float height;

        Canvas(const KRL::Frame &origin, float width, float height);

        /// An unordered set of Draw2D::Commands that should be drawn with respect to this Canvas.
        std::vector<std::unique_ptr<Draw2D::Command>> commands;

        /// @returns Returns a string representing this Canvas and each Draw2D::Command that it contains.
        std::string compileKRL() override;

        /// @returns Returns a Path representing the boundaries of the canvas.
        Kaironetic::Draw2D::Path *drawBoundaries() const;

        /// @brief Converts a given Draw2DPoint to a Frame that represents that position in the workspace.
        KRL::Frame pointToFrame(Draw2D::Point input) const;

        /// @returns Returns a Frame representing the pen-up position.
        KRL::Frame penUp();

        /// @returns Returns a Frame representing the pen-down position.
        KRL::Frame penDown();
    };
}
#endif //SYNTH_CANVAS_H
