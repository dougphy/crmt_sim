#### CMAKE FILE :: DOUGLAS DAVIS <douglasdavis@utexas.edu>

cmake_minimum_required(VERSION 2.8)
project(crmt)

## -- set some cmake variables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_CXX_FLAGS "-g -Wall -O3 -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})

## -- boost
find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})

## -- prepare ROOT
find_package(ROOT REQUIRED)
include_directories(${ROOT_INC_DIR})
link_directories(${ROOT_LIB_DIR})

## -- prepare project include and lib dirs
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

##### COMPILE CRMT LIBRARIES
## -- setup to compile libraries
add_library(Ev SHARED src/evg.cxx src/evd.cxx)
add_library(Geo SHARED src/Line.cxx src/Module.cxx src/TestVolume.cxx)
## -- add library dependencies
target_link_libraries(Geo ${ROOT_LIBS})
target_link_libraries(Ev ${ROOT_LIBS} Geo)

##### COMPILE CRMT EXECUTABLE
## -- setup to compile executable 
add_executable(crmt crmt.cxx)
## -- add executable dependencies
target_link_libraries(crmt ${ROOT_LIBS} Ev Geo ${Boost_PROGRAM_OPTIONS_LIBRARY})

add_subdirectory(geo_test)