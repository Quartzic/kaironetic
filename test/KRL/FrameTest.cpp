#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file

#include "catch.hpp"
#include "KRL/Frame.h"

TEST_CASE("Compile Frame to KRL") {
    SECTION("Compile empty Frame (empty constructor)") {
        REQUIRE(Kaironetic::KRL::Frame().compileKRL() ==
                "{}");
    }

    SECTION("Compile empty Frame (empty options)") {
        REQUIRE(Kaironetic::KRL::Frame({}, {}, {}, {}, {}, {}).compileKRL() ==
                "{}");
    }

    SECTION("Compile empty Frame (nullopt)") {
        REQUIRE(Kaironetic::KRL::Frame(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt,
                                       std::nullopt).compileKRL() ==
                "{}");
    }

    SECTION("Compile partially initialized Frame") {
        REQUIRE(Kaironetic::KRL::Frame(100, {}, {}, {}, {}, {}).compileKRL() ==
                "{X 100.000000}");
    }

    SECTION("Compile fully initialized Frame") {
        REQUIRE(Kaironetic::KRL::Frame(100, 200, 300, 30, 90, 180).compileKRL() ==
                "{X 100.000000,Y 200.000000,Z 300.000000,A 30.000000,B 90.000000,C 180.000000}");
    }

}

TEST_CASE("Frame equality operator") {
    SECTION("Identical Frames are equal") {
        REQUIRE((Kaironetic::KRL::Frame(100, 200, 300, 30, 90, 180) ==
                 Kaironetic::KRL::Frame(100, 200, 300, 30, 90, 180)));
    }


    SECTION("Frames initialized with nullopt equal those initialized with an empty constructor") {
        REQUIRE((Kaironetic::KRL::Frame(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt,
                                        std::nullopt) ==
                 Kaironetic::KRL::Frame({})));
    }

    SECTION("Non-identical Frames are not equal") {
        REQUIRE(!(Kaironetic::KRL::Frame(100, 200, 300, 30, 90, 180) ==
                  Kaironetic::KRL::Frame(200, 300, 400, 60, 180, 360)));
    }

    SECTION("Frames with different valued initializations are not equal") {
        REQUIRE(!(Kaironetic::KRL::Frame(100, 200, 300, 30, 90, 180) ==
                  Kaironetic::KRL::Frame(100, {}, {}, {}, {}, {})));
    }
}


TEST_CASE("Frame addition operator") {
    SECTION("Add fully initialized frames") {
        REQUIRE(((Kaironetic::KRL::Frame(100, 200, 300, 30, 90, 180) +
                  Kaironetic::KRL::Frame(100, 200, 300, 30, 90, 180)) ==
                 Kaironetic::KRL::Frame(200, 400, 600, 60, 180, 360)));
    }SECTION("Add partially initialized frames") {
        REQUIRE(((Kaironetic::KRL::Frame({}, {}, {}, 30, 90, 180) +
                  Kaironetic::KRL::Frame(100, 200, 300, {}, {}, {})) ==
                 Kaironetic::KRL::Frame(100, 200, 300, 30, 90, 180)));
    }SECTION("Add empty frames") {
        REQUIRE((Kaironetic::KRL::Frame({}) +
                 Kaironetic::KRL::Frame({}) ==
                 Kaironetic::KRL::Frame({})));
    }

}
