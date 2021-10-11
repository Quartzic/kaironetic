
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
    /// \brief Represents a two-dimensional path
    class Path : public Draw2D::Command {
    public:
        std::__1::vector<Draw2D::Point> points;

        Path(const std::__1::vector<Draw2D::Point> &points);

        /// Get the first point
        Draw2D::Point getStartPoint() override;

        /// Get the last point
        Draw2D::Point getEndPoint() override;

        std::string compileKRL(Draw2D::Canvas *canvas) override;
    };
}

#endif //SYNTH_PATH_H
