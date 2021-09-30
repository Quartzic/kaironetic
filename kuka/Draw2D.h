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

class Draw2DPoint {
 public:
  float x;
  float y;
  Draw2DPoint(float x, float y);
};
class Draw2DPenUp : public Command {
 public:
  const std::string compileKRL() override;
  Draw2DPenUp();
};
class Draw2DPenDown : public Command {
 public:
  const std::string compileKRL() override;
  Draw2DPenDown();
};
class Draw2DLine : public Command {
 public:
  float x1;
  float y1;
  float x2;
  float y2;
  Draw2DLine(float x1, float y1, float x2, float y2);
  const std::string compileKRL() override;
};
class Draw2DSquare : public Command {
 public:
  float x;
  float y;
  float length;
  float width;
  Draw2DSquare(float x, float y, float length, float width);
  const std::string compileKRL() override;
};
class Draw2DPath : public Command {
 public:
  std::vector<Draw2DPoint> points;
  Draw2DPath(const std::vector<Draw2DPoint>& points);
  const std::string compileKRL() override;
};
class Draw2DSpline : public Command {
 public:
  std::vector<Draw2DPoint> points;
  Draw2DSpline(const std::vector<Draw2DPoint>& points);
  const std::string compileKRL() override;
};
};  // namespace Kuka

#endif  // SYNTH_DRAW2D_H
