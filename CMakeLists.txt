cmake_minimum_required(VERSION 3.17)
project(synth)

find_package( OpenCV REQUIRED )
find_package( Boost REQUIRED COMPONENTS program_options )
find_package( fmt REQUIRED )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_APPLE_SILICON_PROCESSOR arm64)

add_executable(synth main.cpp)

# CMake instructions to make the static lib

ADD_LIBRARY(kaironetic STATIC kaironetic/Command.cpp kaironetic/Draw2D.cpp kaironetic/Frame.cpp kaironetic/Group.cpp)

include_directories( ${Boost_INCLUDE_DIRS} include/ )
target_link_libraries( synth ${Boost_PROGRAM_OPTIONS_LIBRARY} )
target_link_libraries( synth ${OpenCV_LIBS} )
target_link_libraries( synth fmt::fmt)
target_link_libraries( synth kaironetic)
