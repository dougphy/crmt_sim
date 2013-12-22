cmake_minimum_required(VERSION 2.8)
project(crmt)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_CXX_FLAGS "-g -m64 -O3 -std=c++11")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})

find_package(ROOT REQUIRED)
include_directories(${ROOT_INC_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${ROOT_LIB_DIR})

add_library(Gen SHARED src/evg.cxx)
add_library(Disp SHARED src/evd.cxx)
add_library(Geo SHARED src/Line.cxx src/Module.cxx src/TestVolume.cxx)

target_link_libraries(Geo ${ROOT_LIBS})
target_link_libraries(Gen ${ROOT_LIBS} Geo)
target_link_libraries(Disp ${ROOT_LIBS} Geo Gen)

add_executable(crmt crmt.cxx)
target_link_libraries(crmt ${ROOT_LIBS} Gen Disp Geo)
