cmake_minimum_required(VERSION 2.8)
project(crmt)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_CXX_FLAGS "-g -m64 -O3 -std=c++11")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})

find_package(ROOT REQUIRED)
include_directories(${ROOT_INC_DIR})
link_directories(${ROOT_LIB_DIR})

add_executable(crmt src/crmt.cxx src/Module.cxx src/Line.cxx src/TestVolume.cxx src/evg.cxx src/evd.cxx)
target_link_libraries(crmt ${ROOT_LIBS})
