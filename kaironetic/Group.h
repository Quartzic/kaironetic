//
// Created by Nathan Goller-Deitsch on 9/21/21.
//

#ifndef SYNTH_GROUP_H
#define SYNTH_GROUP_H

#include <vector>
#include <memory>

#include "Command.h"

namespace Kaironetic {
    class Group {
    public:
        std::vector<std::unique_ptr<Kaironetic::Command>> commands;

        std::string compileKRL();
    };
}  // namespace Kuka
#endif  // SYNTH_GROUP_H
