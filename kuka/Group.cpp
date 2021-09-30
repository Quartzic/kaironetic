//
// Created by Nathan Goller-Deitsch on 9/21/21.
//

#include "Group.h"
std::string Kuka::Group::compileKRL() {
  std::string output;
  for (int i = 0; i < commands.size(); i++) {
    output += (commands[i]->compileKRL() + "\n");
  }
  return output;
}
