//
// Created by Nathan Goller-Deitsch on 9/20/21.
//

#ifndef SYNTH_FRAME_H
#define SYNTH_FRAME_H

#include <string>
#include <optional>

namespace Kuka {
class Frame {
 public:
  std::string compileKRL();
  std::optional<float> x;
  std::optional<float> y;
  std::optional<float> z;
  std::optional<float> a;
  std::optional<float> b;
  std::optional<float> c;
  Frame(const std::optional<float>& x, const std::optional<float>& y,
        const std::optional<float>& z, const std::optional<float>& a,
        const std::optional<float>& b, const std::optional<float>& c);
};
}
#endif  // SYNTH_FRAME_H
