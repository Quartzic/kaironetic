cmake_minimum_required(VERSION 3.20)
project(kaironetic)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_APPLE_SILICON_PROCESSOR arm64)

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)
find_package(Catch2 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} include/ src/)

# kaironetic library
add_library(kaironetic src/Draw2D/Canvas.cpp src/Draw2D/Command.h src/Draw2D/Path.cpp src/Draw2D/Point.cpp src/KRL/Command.cpp src/KRL/Frame.cpp src/KRL/Group.cpp)
target_link_libraries(kaironetic ${Boost_LIBRARIES})

# tests
add_executable(tests test/KRL/FrameTest.cpp test/Draw2D/CanvasTest.cpp)
target_link_libraries(tests kaironetic)
target_link_libraries(tests Catch2::Catch2)

include(CTest)
include(Catch)

enable_testing()
catch_discover_tests(tests)

# examples
add_executable(draw_evenly_spaced_lines example/draw_evenly_spaced_lines.cpp)
target_link_libraries(draw_evenly_spaced_lines kaironetic)
target_link_libraries(draw_evenly_spaced_lines ${OpenCV_LIBS})