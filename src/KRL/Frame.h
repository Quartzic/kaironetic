

#ifndef SYNTH_FRAME_H
#define SYNTH_FRAME_H

#include <optional>
#include <string>

namespace Kaironetic::KRL {
    /// \brief Data structure representing an arm position

    class Frame {
    public:
        Frame();

        /// Adds two Frames together
        Frame operator+(const Frame &rhs);

        /// Checks if Frames are equal to each other
        bool operator==(const Frame &rhs);

        /// \returns Returns a string representing this Frame in KRL.
        std::string compileKRL();

        /// Value of the X axis, in millimeters
        std::optional<float> x;
        /// Value of the Y axis, in millimeters
        std::optional<float> y;
        /// Value of the Z axis, in millimeters
        std::optional<float> z;
        /// Value of the A axis, in degrees
        std::optional<float> a;
        /// Value of the B axis, in degrees
        std::optional<float> b;
        /// Value of the C axis, in degrees
        std::optional<float> c;

        Frame(const std::optional<float> &x, const std::optional<float> &y,
              const std::optional<float> &z, const std::optional<float> &a,
              const std::optional<float> &b, const std::optional<float> &c);
    };
}  // namespace Kuka
#endif  // SYNTH_FRAME_H
