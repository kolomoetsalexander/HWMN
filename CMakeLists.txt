cmake_minimum_required(VERSION 3.16)
project(HWMN)

set(CMAKE_CXX_STANDARD 17)

#library
add_library(hwmn INTERFACE)
target_include_directories(hwmn INTERFACE include)

#benchmarks
add_executable(HWMN benchmarks/main.cpp)
target_link_libraries(HWMN PRIVATE hwmn)

target_include_directories(HWMN PRIVATE
    ${CMAKE_SOURCE_DIR}
)
target_link_libraries(HWMN PRIVATE hwmn)

#GoogleTests
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
FetchContent_MakeAvailable(googletest)

#tests
enable_testing()

add_executable(hwmn_tests
    tests/MatrixTests.cpp
    tests/JaggedMatrixTests.cpp
    tests/GaussianTests.cpp
    tests/BareissTests.cpp
    tests/MatrixGeneratorTests.cpp
    tests/LargeMatrixTests.cpp
)
target_include_directories(hwmn_tests PRIVATE
    ${CMAKE_SOURCE_DIR}
)
target_link_libraries(hwmn_tests PRIVATE hwmn GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(hwmn_tests)
