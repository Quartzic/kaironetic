
#ifndef SYNTH_PATH_H
#define SYNTH_PATH_H

#include <boost/algorithm/string/join.hpp>
#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include "Point.h"
#include "Command.h"
#include "Canvas.h"

using namespace Kaironetic;

namespace Kaironetic::Draw2D {
    /// \brief Two-dimensional path
    class Path : public Draw2D::Command {
    public:
        /// An ordered set of Points that the tool should travel through
        std::vector<Draw2D::Point> points;

        /// Construct a Path given a set of Points
        Path(const std::vector<Draw2D::Point> &points);

        /// Get the first Point
        Draw2D::Point getStartPoint() override;

        /// Get the last Point
        Draw2D::Point getEndPoint() override;

        std::string compileKRL(Draw2D::Canvas *canvas) override;
    };

    Path *drawRectangle(Point origin, float width, float height);
}

#endif //SYNTH_PATH_H
