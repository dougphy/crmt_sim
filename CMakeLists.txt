cmake_minimum_required(VERSION 2.8)
project(crmt)

set(CMAKE_CXX_FLAGS "-g -m64 -O3 -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "-g -m64 -stdlib=libc++")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

include_directories("${CMAKE_SOURCE_DIR}/src")
include_directories("/opt/local/include/root")
link_directories("/opt/local/lib/root")

add_executable(crmt src/crmt.cxx src/Module.cxx src/Line.cxx src/TestVolume.cxx src/evg.cxx src/evd.cxx)
target_link_libraries(crmt Core Cint RIO Net Hist Graf Graf3d Gpad Tree Rint Postscript Matrix Physics MathCore Thread pthread m dl)
