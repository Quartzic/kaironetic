//
// Created by Nathan Goller-Deitsch on 9/21/21.
//

#ifndef SYNTH_GROUP_H
#define SYNTH_GROUP_H

#include <vector>

#include "Command.h"
namespace Kuka {
class Group {
 public:
  std::vector<std::unique_ptr<Kuka::Command>> commands;
  std::string compileKRL();
};
}
#endif  // SYNTH_GROUP_H
