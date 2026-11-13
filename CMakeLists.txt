cmake_minimum_required(VERSION 3.16)
project(HWMN)

set(CMAKE_CXX_STANDARD 17)

add_library(hwmn
    src/determinant/Gaussian.cpp
    src/determinant/Bareiss.cpp
    src/determinant/Determinant.cpp
)

target_include_directories(hwmn PUBLIC include)

add_executable(HWMN src/main.cpp)
target_link_libraries(HWMN PRIVATE hwmn)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(hwmn_tests
    tests/MatrixTests.cpp
    tests/JaggedMatrixTests.cpp
    tests/GaussianTests.cpp
    tests/BarreissTests.cpp
)

target_link_libraries(hwmn_tests PRIVATE hwmn GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(hwmn_tests)
