#include "catch.hpp"
#include "Draw2D/Canvas.h"

TEST_CASE("Canvas constructor") {
    SECTION("Construct properly formed Canvas") {
        REQUIRE_NOTHROW(
                Kaironetic::Draw2D::Canvas(Kaironetic::KRL::Frame(100, 200, 300, 30, 90, 180), 50, 50)
        );
    }SECTION("Can't construct Canvas with partially initialized Frame") {
        REQUIRE_THROWS(
                Kaironetic::Draw2D::Canvas(Kaironetic::KRL::Frame(100, 200, 300, 30, 0, std::nullopt), 50, 50)
        );
    }
}

TEST_CASE("Canvas drawing") {
    Kaironetic::Draw2D::Canvas canvas(Kaironetic::KRL::Frame(100, 200, 300, 30, 90, 180), 50, 50);
    SECTION("Point transformed to valid appropriate Frame") {
        Kaironetic::Draw2D::Point inputPoint = Draw2D::Point(25, 30);
        Kaironetic::KRL::Frame expectedFrame(125, 170, {}, {}, {}, {});
        REQUIRE((canvas.pointToFrame(inputPoint) == expectedFrame));
    }SECTION("Can't draw outside of Canvas") {
        Kaironetic::Draw2D::Point invalidPoint = Draw2D::Point(0, 75);
        REQUIRE_THROWS(canvas.pointToFrame(invalidPoint));
    }SECTION("Pen down returns Frame with origin's Z axis") {
        REQUIRE((canvas.penDown() == Kaironetic::KRL::Frame({}, {}, 300, {}, {}, {})));
    }SECTION("Pen up returns Frame with modified value") {
        REQUIRE((canvas.penUp() == Kaironetic::KRL::Frame({}, {}, 305, {}, {}, {})));
    }


}