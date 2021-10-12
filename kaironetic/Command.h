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

namespace Kaironetic {

class Command {
 public:
  virtual const std::string compileKRL() = 0;
};

class Comment : public Command {
 public:
  const std::string compileKRL() override;
  Comment(std::string comment);
  std::string comment;
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
class SPL : public Command {
 public:
  const std::string compileKRL() override;
  Frame frame;
  SPL(Frame);
};
class SPLINE : public Command {
 public:
  const std::string compileKRL() override;
};
class ENDSPLINE : public Command {
 public:
  const std::string compileKRL() override;
};
}  // namespace Kuka
#endif  // SYNTH_COMMAND_H
