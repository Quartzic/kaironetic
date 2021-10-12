//
// Created by Nathan Goller-Deitsch on 9/29/21.
//

#include <cmath>
#include "Draw2D.h"

#include "Command.h"
#include "Group.h"

#define PEN_UP_MM 10

const std::string Kaironetic::Draw2DPath::compileKRL(Draw2DCanvas * canvas) {
  Kaironetic::Group output;
  output.commands.emplace_back(
      new Kaironetic::LIN(canvas->pointToFrame(points[0])));
  output.commands.emplace_back(new Kaironetic::LIN(canvas->penDown()));
  for (int i = 1; i < points.size(); i++) {
    output.commands.emplace_back(
        new Kaironetic::LIN(canvas->pointToFrame(points[i])));
  }
  output.commands.emplace_back(new Kaironetic::LIN(canvas->penUp()));
  return output.compileKRL();
}
Kaironetic::Draw2DPath::Draw2DPath(const std::vector<Draw2DPoint>& points)
    : points(points) {}

    /// @returns test
const Kaironetic::Draw2DPoint Kaironetic::Draw2DPath::getStartPoint() {
    return this->points[0];
}
const Kaironetic::Draw2DPoint Kaironetic::Draw2DPath::getEndPoint() {
    return this->points[this->points.size()];
}

const std::string Kaironetic::Draw2DSpline::compileKRL(Draw2DCanvas * canvas) {
    Kaironetic::Group output;
    output.commands.emplace_back(
            new Kaironetic::LIN(canvas->pointToFrame(points[0])));
    output.commands.emplace_back(new Kaironetic::LIN(canvas->penDown()));
    output.commands.emplace_back(new Kaironetic::SPLINE);
    for (int i = 0; i < points.size(); i++) {
        output.commands.emplace_back(
                new Kaironetic::SPL(canvas->pointToFrame(points[i])));
    }
    output.commands.emplace_back(new Kaironetic::ENDSPLINE);
    output.commands.emplace_back(new Kaironetic::LIN(canvas->penUp()));
    return output.compileKRL();
}
Kaironetic::Draw2DSpline::Draw2DSpline(const std::vector<Draw2DPoint>& points)
        : points(points) {}

const Kaironetic::Draw2DPoint Kaironetic::Draw2DSpline::getStartPoint() {
    return this->points[0];
}
const Kaironetic::Draw2DPoint Kaironetic::Draw2DSpline::getEndPoint() {
    return this->points[this->points.size()];
}

Kaironetic::Draw2DPoint::Draw2DPoint(float x, float y) : x(x), y(y) {}

float Kaironetic::Draw2DPoint::distanceTo(Kaironetic::Draw2DPoint input) {
    return sqrt(pow(this->x - input.x, 2) +
                pow(this->y - input.y, 2) * 1.0);
}

Kaironetic::Draw2DCanvas::Draw2DCanvas(const Kaironetic::Frame &origin, const float width, const float height) : origin(origin), width(width), height(height) {
    if(!(origin.x && origin.y && origin.z && origin.a && origin.b && origin.c)){
        throw std::invalid_argument("can't construct canvas with incomplete frame");
    }
}

Kaironetic::Frame Kaironetic::Draw2DCanvas::pointToFrame(Kaironetic::Draw2DPoint input) {

    if(input.x > this->width || input.x < 0 || input.y > this->height || input.y < 0){
        throw std::invalid_argument("can't draw outside of frame");
    }

    return Kaironetic::Frame(origin.x, origin.y, {}, {}, {}, {}) + Kaironetic::Frame(input.x, -input.y, {}, {}, {}, {});
}

/// Uses a nearest-neighbor algorithm to sort Draw2DCommands by distance. Returns KRL to draw every Draw2DCommand in this Draw2DCanvas.
const std::string Kaironetic::Draw2DCanvas::compileKRL() {
    std::string output;
    output += Kaironetic::PTP(origin + Kaironetic::Frame({}, {}, 100, {}, {}, {})).compileKRL() + "\n";

    Kaironetic::Draw2DPoint lastVisitedPoint = Draw2DPoint(0, 0);

    while(commands.size() > 0) {
        float cheapestNextDistance = 0;
        int cheapestNextCommand = 0;
        std::cout << std::endl << "finding cheapest next shape to draw" << std::endl;
        for (int i = 0; i < commands.size(); i++) {

            float possibleDistance = lastVisitedPoint.distanceTo(commands[i]->getStartPoint());
            std::cout << "distance to shape " << i << " is " << possibleDistance << std::endl;
            if(possibleDistance < cheapestNextDistance){
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

Kaironetic::Frame Kaironetic::Draw2DCanvas::penUp() {
    return Kaironetic::Frame({}, {}, this->origin.z.value() + PEN_UP_MM, {}, {}, {});
}

/// test
Kaironetic::Frame Kaironetic::Draw2DCanvas::penDown() {
    return Kaironetic::Frame({}, {}, this->origin.z.value(), {}, {}, {});
}

Kaironetic::Draw2DPath* Kaironetic::Draw2DCanvas::drawBoundaries() {
    return new Kaironetic::Draw2DPath({Draw2DPoint(0, 0), Draw2DPoint(width, 0), Draw2DPoint(width, height), Draw2DPoint(0, height), Draw2DPoint(0, 0)});
}

