//
// Created by Nathan Goller-Deitsch on 9/29/21.
//

#include <cmath>
#include "Draw2D.h"

#include "Command.h"
#include "Group.h"

#define PEN_UP_MM 10

const std::string Kuka::Draw2DPath::compileKRL(Draw2DCanvas * canvas) {
  Kuka::Group output;
  output.commands.emplace_back(
      new Kuka::LIN(canvas->pointToFrame(points[0])));
  output.commands.emplace_back(new Kuka::LIN(canvas->penDown()));
  for (int i = 1; i < points.size(); i++) {
    output.commands.emplace_back(
        new Kuka::LIN(canvas->pointToFrame(points[i])));
  }
  output.commands.emplace_back(new Kuka::LIN(canvas->penUp()));
  return output.compileKRL();
}
Kuka::Draw2DPath::Draw2DPath(const std::vector<Draw2DPoint>& points)
    : points(points) {}

const Kuka::Draw2DPoint Kuka::Draw2DPath::getStartPoint() {
    return this->points[0];
}
const Kuka::Draw2DPoint Kuka::Draw2DPath::getEndPoint() {
    return this->points[this->points.size()];
}

Kuka::Draw2DPoint::Draw2DPoint(float x, float y) : x(x), y(y) {}

float Kuka::Draw2DPoint::distanceTo(Kuka::Draw2DPoint input) {
    return sqrt(pow(this->x - input.x, 2) +
                pow(this->y - input.y, 2) * 1.0);
}

/*const std::string Kuka::Draw2DSpline::compileKRL() {
  Kuka::Group output;
  output.commands.emplace_back(
      new Kuka::LIN(Kuka::Frame(points[0].x, points[0].y, std::nullopt,
                                std::nullopt, std::nullopt, std::nullopt)));
  output.commands.emplace_back(new Kuka::Draw2DPenDown);
  output.commands.emplace_back(new Kuka::SPLINE);
  for (int i = 0; i < points.size(); i++) {
    output.commands.emplace_back(
        new Kuka::SPL(Kuka::Frame(points[i].x, points[i].y, std::nullopt,
                                  std::nullopt, std::nullopt, std::nullopt)));
  }
  output.commands.emplace_back(new Kuka::ENDSPLINE);
  output.commands.emplace_back(new Kuka::Draw2DPenUp);
  return output.compileKRL();
}*/

Kuka::Draw2DCanvas::Draw2DCanvas(const Kuka::Frame &origin, const float width, const float height) : origin(origin), width(width), height(height) {
    if(!(origin.x && origin.y && origin.z && origin.a && origin.b && origin.c)){
        throw std::invalid_argument("can't construct canvas with incomplete frame");
    }
}

Kuka::Frame Kuka::Draw2DCanvas::pointToFrame(Kuka::Draw2DPoint input) {

    if(input.x > this->width || input.x < 0 || input.y > this->height || input.y < 0){
        throw std::invalid_argument("can't draw outside of frame");
    }

    return Kuka::Frame(origin.x, origin.y, {},{},{},{}) + Kuka::Frame(input.x, -input.y, {}, {}, {}, {});
}

const std::string Kuka::Draw2DCanvas::compileKRL() {
    std::string output;
    output += Kuka::PTP(origin + Kuka::Frame({},{},100,{},{},{})).compileKRL() + "\n";

    Kuka::Draw2DPoint lastVisitedPoint = Draw2DPoint(0,0);

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

Kuka::Frame Kuka::Draw2DCanvas::penUp() {
    return Kuka::Frame({},{},this->origin.z.value() + PEN_UP_MM,{},{},{});
}

Kuka::Frame Kuka::Draw2DCanvas::penDown() {
    return Kuka::Frame({},{},this->origin.z.value(),{},{},{});
}

Kuka::Draw2DPath* Kuka::Draw2DCanvas::drawBoundaries() {
    return new Kuka::Draw2DPath({Draw2DPoint(0,0), Draw2DPoint(width, 0), Draw2DPoint(width, height), Draw2DPoint(0, height), Draw2DPoint(0,0)});
}

