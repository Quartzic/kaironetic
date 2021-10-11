
#ifndef SYNTH_POINT_H
#define SYNTH_POINT_H

namespace Kaironetic::Draw2D {
    /// \brief Two-dimensional point
    class Point {
    public:
        float x;
        float y;

        Point(float x, float y);

        [[nodiscard]] float distanceTo(Point input) const;
    };
}
#endif //SYNTH_POINT_H
