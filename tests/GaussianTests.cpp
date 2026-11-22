#include <gtest/gtest.h>
#include "matrix/Matrix.hpp"
#include "determinant/Gaussian.hpp"
#include "matrix/JaggedMatrix.hpp"

TEST(GaussianTests, TwoByTwo){
    Matrix<double> a(2, 2);
    a(0, 0) = 1;
    a(0, 1) = 2;
    a(1, 0) = 3;
    a(1, 1) = 4;
    //there will definitely be some error
    EXPECT_NEAR(gaussian(a), -2.0, 1e-9);
}
TEST(GaussianTests, IdentityMatrix){
    Matrix<double> a(3, 3);
    for (size_t i = 0; i < 3; ++i){
        a(i, i) = 1.0;
    }

    EXPECT_NEAR(gaussian(a), 1.0, 1e-9);
}
TEST(GaussianTests, SingularMatrix){
    Matrix<double> a(2, 2);
    a(0, 0) = 1;
    a(0, 1) = 2;
    a(1, 0) = 2;
    a(1, 1) = 4;

    EXPECT_NEAR(gaussian(a), 0.0, 1e-9);
}
TEST(GaussianTests, RowSwap){
    Matrix<double> a(2, 2);
    a(0, 0) = 0;
    a(0, 1) = 2;
    a(1, 0) = 3;
    a(1, 1) = 4;

    EXPECT_NEAR(gaussian(a), -6.0, 1e-9);
}
TEST(GaussianTests, OneByOne){
    Matrix<double> a(1, 1);
    a(0, 0) = 7.0;

    EXPECT_NEAR(gaussian(a), 7.0, 1e-9);
}
//when we creating an internal copy, the original matrix should not be modified (temp)
TEST(GaussianTests, OriginalMatrixUnchanged){
    Matrix<double> a(2, 2);
    a(0, 0) = 1;
    a(0, 1) = 2;
    a(1, 0) = 3;
    a(1, 1) = 4;

    gaussian(a);

    EXPECT_EQ(a(0, 0), 1);
    EXPECT_EQ(a(0, 1), 2);
    EXPECT_EQ(a(1, 0), 3);
    EXPECT_EQ(a(1, 1), 4);
}
TEST(GaussianTests, JaggedMatrix){
    JaggedMatrix<double> a(2, 2);
    a(0, 0) = 1.0;
    a(0, 1) = 2.0;
    a(1, 0) = 3.0;
    a(1, 1) = 4.0;

    EXPECT_NEAR(gaussian(a), -2.0, 1e-9);
}
TEST(GaussianTests, NonSquareMatrix){
    Matrix<double> a(2, 3);

    EXPECT_THROW(gaussian(a), std::invalid_argument);
}
TEST(GaussianTests, NonSquareJaggedMatrix){
    JaggedMatrix<double> a(2, 3);

    EXPECT_THROW(gaussian(a), std::invalid_argument);
}
TEST(GaussianTests, EmptyMatrix){
    Matrix<double> a(0, 0);

    EXPECT_EQ(gaussian(a), 1);
}
TEST(GaussianTests, EmptyJaggedMatrix){
    JaggedMatrix<double> a(0, 0);

    EXPECT_EQ(gaussian(a), 1);
}
//function for cheking
template<template<typename> class Container, typename T>
void checkGaussian(){
    Container<T> matrix(2, 2);

    matrix(0, 0) = 2;
    matrix(0, 1) = 3;
    matrix(1, 0) = 1;
    matrix(1, 1) = 4;

    EXPECT_NEAR(gaussian(matrix), 5.0L, 1e-9L);
}

TEST(GaussianTests, DifferentTypesContiguous){
    checkGaussian<Matrix, int>();
    checkGaussian<Matrix, long long>();
    checkGaussian<Matrix, float>();
    checkGaussian<Matrix, double>();
    checkGaussian<Matrix, long double>();
}

TEST(GaussianTests, DifferentTypesJagged){
    checkGaussian<JaggedMatrix, int>();
    checkGaussian<JaggedMatrix, long long>();
    checkGaussian<JaggedMatrix, float>();
    checkGaussian<JaggedMatrix, double>();
    checkGaussian<JaggedMatrix, long double>();
}