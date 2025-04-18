#
# ViterbiTrellis library cmake
# Copyright (c) 2025 Eray Ozturk <erayozturk1@gmail.com>
#
cmake_minimum_required(VERSION 3.10)
project(ViterbiTrellis)

set(CMAKE_CXX_STANDARD 11)

add_executable(ViterbiTrellis main.cpp)

add_executable(helper helper.cpp)

enable_testing()
find_package(GTest REQUIRED)
add_executable(ViterbiTrellisTest ViterbiTrellisTest.cpp)
target_link_libraries(
    ViterbiTrellisTest
    PRIVATE 
    GTest::GTest 
    GTest::Main
)
include(GoogleTest)
gtest_discover_tests(ViterbiTrellisTest)
