//
// Created by Nathan Goller-Deitsch on 9/20/21.
//
#ifndef SYNTH_COMMAND_H
#define SYNTH_COMMAND_H
#include <boost/algorithm/string/join.hpp>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "Frame.h"

namespace Kuka {

class Command {
 public:
  virtual const std::string compileKRL() = 0;
};

class STARTWRAPPER : public Command {
 public:
  const std::string compileKRL() override;
};

class ENDWRAPPER : public Command {
 public:
  const std::string compileKRL() override;
};
class LIN : public Command {
 public:
  const std::string compileKRL() override;
  Frame frame;
  LIN(Frame);
};

class PTP : public Command {
 public:
  const std::string compileKRL() override;
  Frame frame;
  PTP(Frame);
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
}
#endif  // SYNTH_COMMAND_H
