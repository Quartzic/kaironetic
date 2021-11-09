#ifndef SYNTH_COMMAND_H
#define SYNTH_COMMAND_H

#include <boost/algorithm/string/join.hpp>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "Frame.h"

namespace Kaironetic::KRL {

    /// \brief A structure that can be compiled into KRL
    class Command {
    public:
        virtual std::string compileKRL() = 0;
    };

    /// \brief Single-line comment
    class Comment : public Command {
    public:
        std::string compileKRL() override;

        Comment(const std::string &comment);

        std::string comment;
    };

    /// \brief Setup commands
    ///
    /// Must be placed at the start of your program.
    class STARTWRAPPER : public Command {
    public:
        std::string compileKRL() override;
    };

    /// \brief Teardown commands
    ///
    /// Must be placed at the end of your program.
    class ENDWRAPPER : public Command {
    public:
        std::string compileKRL() override;
    };


    /// Linear movement
    class LIN : public Command {
    public:
        std::string compileKRL() override;

        Frame frame;

        LIN(Frame);
    };

    /// \brief Point-to-point movement
    ///
    /// This movement will prioritize speed over smoothness.
    class PTP : public Command {
    public:
        std::string compileKRL() override;

        Frame frame;

        PTP(Frame);
    };

    /// \brief Spline movement
    ///
    /// Must be placed within a SPLINE block.
    class SPL : public Command {
    public:
        std::string compileKRL() override;

        Frame frame;

        SPL(Frame);
    };

    /// \brief Marks the start of a spline movement
    ///
    /// This must be followed by at least one SPL command and an ENDSPLINE command.
    class SPLINE : public Command {
    public:
        std::string compileKRL() override;
    };

    /// \brief Marks the end of a spline movement
    ///
    /// Must be preceded by a SPLINE command and at least one SPL command.
    class ENDSPLINE : public Command {
    public:
        std::string compileKRL() override;
    };
}  // namespace Kuka
#endif  // SYNTH_COMMAND_H
