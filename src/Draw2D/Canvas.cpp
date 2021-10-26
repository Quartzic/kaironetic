#include "Canvas.h"

using namespace Kaironetic;

Draw2D::Canvas::Canvas(const KRL::Frame &origin, const float width, const float height) : origin(origin), width(width),
                                                                                          height(height) {
    if (!(origin.x && origin.y && origin.z && origin.a && origin.b && origin.c)) {
        throw std::invalid_argument("can't construct canvas with incomplete frame");
    }
}

KRL::Frame Draw2D::Canvas::pointToFrame(Kaironetic::Draw2D::Point input) const {

    if (input.x > this->width || input.x < 0 || input.y > this->height || input.y < 0) {
        throw std::invalid_argument("can't draw outside of frame");
    }

    return KRL::Frame(origin.x, origin.y, {}, {}, {}, {}) + KRL::Frame(input.x, -input.y, {}, {}, {}, {});
}

/// Uses a nearest-neighbor algorithm to sort by distance; then, returns KRL to draw every Draw2D::Command in this Canvas.
std::string Draw2D::Canvas::compileKRL() {
    std::string output;
    output += KRL::PTP(origin + KRL::Frame({}, {}, 100, {}, {}, {})).compileKRL() + "\n";

    Kaironetic::Draw2D::Point lastVisitedPoint = Draw2D::Point(0, 0);

    while (!commands.empty()) {
        float cheapestNextDistance = 0;
        int cheapestNextCommand = 0;
        for (int i = 0; i < commands.size(); i++) {

            float possibleDistance = lastVisitedPoint.distanceTo(commands[i]->getStartPoint());
            if (possibleDistance < cheapestNextDistance) {
                cheapestNextDistance = possibleDistance;
                cheapestNextCommand = i;
                lastVisitedPoint = commands[i]->getEndPoint();
            }

        }

        output += (commands[cheapestNextCommand]->compileKRL(this) + "\n");
        commands.erase(commands.begin() + cheapestNextCommand);
    }
    return output;
}

KRL::Frame Draw2D::Canvas::penUp() {
    return KRL::Frame({}, {}, this->origin.z.value() + 5, {}, {}, {});
}

KRL::Frame Draw2D::Canvas::penDown() {
    return KRL::Frame({}, {}, this->origin.z.value(), {}, {}, {});
}

Kaironetic::Draw2D::Path *Draw2D::Canvas::drawBoundaries() const {
    return new Draw2D::Path(
            {Draw2D::Point(0, 0), Draw2D::Point(width, 0), Draw2D::Point(width, height), Draw2D::Point(0, height),
             Draw2D::Point(0, 0)});
}