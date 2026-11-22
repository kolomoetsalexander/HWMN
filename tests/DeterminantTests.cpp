#include <gtest/gtest.h>
#include <type_traits>

#include "matrix/Matrix.hpp"
#include "matrix/JaggedMatrix.hpp"
#include "determinant/Determinant.hpp"

//we want to check, which algorithm was chousen

template<template<typename> class Container, typename T>
void checkIntegerDeterminant(){
    Container<T> matrix(2, 2);

    matrix(0, 0) = 2;
    matrix(0, 1) = 3;
    matrix(1, 0) = 1;
    matrix(1, 1) = 4;

    auto result = determinant(matrix);

    EXPECT_EQ(result, 5);
    EXPECT_TRUE((std::is_same_v<decltype(result), long long>));
}
template<template<typename> class Container, typename T>
void checkFloatingDeterminant(){
    Container<T> matrix(2, 2);

    matrix(0, 0) = 1.5;
    matrix(0, 1) = 2.0;
    matrix(1, 0) = 3.0;
    matrix(1, 1) = 4.5;

    auto result = determinant(matrix);

    EXPECT_NEAR(result, 0.75L, 1e-9L);
    EXPECT_TRUE((std::is_same_v<decltype(result), long double>));
}
TEST(DeterminantTests, IntegerContiguous){
    checkIntegerDeterminant<Matrix, int>();
    checkIntegerDeterminant<Matrix, long long>();
}
TEST(DeterminantTests, IntegerJagged){
    checkIntegerDeterminant<JaggedMatrix, int>();
    checkIntegerDeterminant<JaggedMatrix, long long>();
}
TEST(DeterminantTests, FloatingContiguous){
    checkFloatingDeterminant<Matrix, float>();
    checkFloatingDeterminant<Matrix, double>();
    checkFloatingDeterminant<Matrix, long double>();
}
TEST(DeterminantTests, FloatingJagged){
    checkFloatingDeterminant<JaggedMatrix, float>();
    checkFloatingDeterminant<JaggedMatrix, double>();
    checkFloatingDeterminant<JaggedMatrix, long double>();
}