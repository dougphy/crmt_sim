include_directories(${CMAKE_SOURCE_DIR})
add_executable(geo_test geo_test.cxx)
target_link_libraries(geo_test ${ROOT_LIBS} Geo)
