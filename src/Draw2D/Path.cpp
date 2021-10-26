
#include "Path.h"
#include "../KRL/Group.h"

std::string Path::compileKRL(Draw2D::Canvas *canvas) {
    KRL::Group output;
    output.commands.emplace_back(
            new KRL::LIN(canvas->pointToFrame(points[0])));
    output.commands.emplace_back(new KRL::LIN(canvas->penDown()));
    for (int i = 1; i < points.size(); i++) {
        output.commands.emplace_back(
                new KRL::LIN(canvas->pointToFrame(points[i])));
    }
    output.commands.emplace_back(new KRL::LIN(canvas->penUp()));
    return output.compileKRL();
}

Path::Path(const std::vector<Draw2D::Point> &points)
        : points(points) {}

Kaironetic::Draw2D::Point Path::getStartPoint() {
    return this->points[0];
}

Kaironetic::Draw2D::Point Path::getEndPoint() {
    return this->points[this->points.size()];
}

Path *Kaironetic::Draw2D::drawRectangle(Point origin, float width, float height) {
    return new Draw2D::Path(
            {Draw2D::Point(origin.x, origin.y), Draw2D::Point(origin.x + width, origin.y),
             Draw2D::Point(origin.x + width, origin.y + height),
             Draw2D::Point(origin.x, origin.y + height),
             Draw2D::Point(origin.x, origin.y)});
}