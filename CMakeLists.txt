cmake_minimum_required(VERSION 3.10)
project(ViterbiTrellis)

set(CMAKE_CXX_STANDARD 11)

add_executable(ViterbiTrellis main.cpp)

add_executable(helper helper.cpp)

enable_testing()
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(ViterbiTrellisTest ViterbiTrellis_test.cpp)
target_link_libraries(ViterbiTrellisTest gtest gtest_main)
add_test(NAME ViterbiTrellisTest COMMAND ViterbiTrellisTest)
