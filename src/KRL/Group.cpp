#include "Group.h"
std::string Kaironetic::KRL::Group::compileKRL() {
  std::string output;
  for (int i = 0; i < commands.size(); i++) {
    output += (commands[i]->compileKRL() + "\n");
  }
  return output;
}
