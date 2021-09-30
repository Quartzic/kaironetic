//
// Created by Nathan Goller-Deitsch on 9/29/21.
//

#include "Draw2D.h"

#include "Command.h"
#include "Group.h"

const std::string Kuka::Draw2DPath::compileKRL() {
  Kuka::Group output;
  output.commands.emplace_back(
      new Kuka::LIN(Kuka::Frame(points[0].x, points[0].y, std::nullopt,
                                std::nullopt, std::nullopt, std::nullopt)));
  output.commands.emplace_back(new Kuka::Draw2DPenDown);
  for (int i = 1; i < points.size(); i++) {
    output.commands.emplace_back(
        new Kuka::LIN(Kuka::Frame(points[i].x, points[i].y, std::nullopt,
                                  std::nullopt, std::nullopt, std::nullopt)));
  }
  output.commands.emplace_back(new Kuka::Draw2DPenUp);
  return output.compileKRL();
}
Kuka::Draw2DPath::Draw2DPath(const std::vector<Draw2DPoint>& points)
    : points(points) {}
Kuka::Draw2DPoint::Draw2DPoint(float x, float y) : x(x), y(y) {}
Kuka::Draw2DSpline::Draw2DSpline(const std::vector<Draw2DPoint>& points)
    : points(points) {}

const std::string Kuka::Draw2DSpline::compileKRL() {
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
}

Kuka::Draw2DPenUp::Draw2DPenUp() {}
const std::string Kuka::Draw2DPenUp::compileKRL() {
  return Kuka::LIN(Kuka::Frame(std::nullopt, std::nullopt, 420, std::nullopt,
                               std::nullopt, std::nullopt))
      .compileKRL();
}

Kuka::Draw2DPenDown::Draw2DPenDown() {}
const std::string Kuka::Draw2DPenDown::compileKRL() {
  return Kuka::LIN(Kuka::Frame(std::nullopt, std::nullopt, 405, std::nullopt,
                               std::nullopt, std::nullopt))
      .compileKRL();
}

Kuka::Draw2DLine::Draw2DLine(float x1, float y1, float x2, float y2)
    : x1(x1), y1(y1), x2(x2), y2(y2) {}

const std::string Kuka::Draw2DLine::compileKRL() {
  Kuka::Group line;
  line.commands.emplace_back(new Kuka::LIN(Kuka::Frame(
      x1, y1, std::nullopt, std::nullopt, std::nullopt, std::nullopt)));
  line.commands.emplace_back(new Kuka::Draw2DPenDown());
  line.commands.emplace_back(new Kuka::LIN(Kuka::Frame(
      x2, y2, std::nullopt, std::nullopt, std::nullopt, std::nullopt)));
  line.commands.emplace_back(new Kuka::Draw2DPenUp());
  return line.compileKRL();
}

const std::string Kuka::Draw2DSquare::compileKRL() {
  return Kuka::Draw2DPath(
             {Kuka::Draw2DPoint(x, y), Kuka::Draw2DPoint(x + length, y),
              Kuka::Draw2DPoint(x + length, y - width),
              Kuka::Draw2DPoint(x, y - width), Kuka::Draw2DPoint(x, y)})
      .compileKRL();
}

Kuka::Draw2DSquare::Draw2DSquare(float x, float y, float length, float width)
    : x(x), y(y), length(length), width(width) {}