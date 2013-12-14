cmake_minimum_required(VERSION 2.8)
project(crmt)

set(CMAKE_CXX_COMPILER=/opt/local/bin/clang++)
set(CMAKE_CXX_FLAGS "-O3 -std=c++11")

include_directories("${CMAKE_SOURCE_DIR}/src")
include_directories("/opt/local/include/root")
link_directories("/opt/local/lib/root")

add_executable(crmt src/Module.cxx src/Line.cxx src/TestVolume.cxx src/evg.cxx src/evd.cxx)
target_link_libraries(crmt Core RIO Net Graf Graf3d Gpad Tree Rint Postscript Matrix Physics MathCore Thread dl)