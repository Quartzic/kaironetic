#ifndef SYNTH_GROUP_H
#define SYNTH_GROUP_H

#include <vector>

#include "Command.h"

namespace Kaironetic::KRL {
    /// \brief Collection of commmands
    class Group {
    public:
        std::__1::vector<std::__1::unique_ptr<Command>> commands;

        /// \returns Returns a string that represents this Group and every nested Command in KRL.
        std::string compileKRL();
    };
}  // namespace Kuka
#endif  // SYNTH_GROUP_H
