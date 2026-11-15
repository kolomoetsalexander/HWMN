#include <gtest/gtest.h>

#include "matrix/Matrix.hpp"
#include "matrix/JaggedMatrix.hpp"
#include "benchmarks/GenerateMatrices.hpp"

TEST(MatrixGeneratorTests, RandomMatrixRange){
    auto matrix = generateRandomMatrix<Matrix<double>>(10, -5.0, 5.0);

    for (size_t i = 0; i < 10; ++i){
        for (size_t j = 0; j < 10; ++j){
            EXPECT_GE(matrix(i, j), -5.0);
            EXPECT_LT(matrix(i, j), 5.0);
        }
    }
}

TEST(MatrixGeneratorTests, SameSeed){
    auto a = generateRandomMatrix<Matrix<long long>>(10, -5LL, 5LL, 42);
    auto b = generateRandomMatrix<Matrix<long long>>(10, -5LL, 5LL, 42);

    for (size_t i = 0; i < 10; ++i){
        for (size_t j = 0; j < 10; ++j){
            EXPECT_EQ(a(i, j), b(i, j));
        }
    }
}

TEST(MatrixGeneratorTests, DifferentLayouts){
    auto a = generateRandomMatrix<Matrix<double>>(10, -5.0, 5.0, 42);
    auto b = generateRandomMatrix<JaggedMatrix<double>>(10, -5.0, 5.0, 42);

    for (size_t i = 0; i < 10; ++i){
        for (size_t j = 0; j < 10; ++j){
            EXPECT_DOUBLE_EQ(a(i, j), b(i, j));
        }
    }
}

TEST(MatrixGeneratorTests, UpperTriangular){
    constexpr size_t N = 10;
    auto matrix = generateUpperTriangularMatrix<Matrix<double>>(N);

    for (size_t i = 0; i < N; ++i){
        EXPECT_DOUBLE_EQ(matrix(i, i), 1.0);

        for (size_t j = 0; j < i; ++j){
            EXPECT_DOUBLE_EQ(matrix(i, j), 0.0);
        }
    }
}

TEST(MatrixGeneratorTests, SingularMatrix){
    constexpr size_t N = 10;
    auto matrix = generateSingularMatrix<Matrix<long long>>(N, -5LL, 5LL);

    for (size_t j = 0; j < N; ++j){
        EXPECT_EQ(matrix(0, j), matrix(N - 1, j));
    }
}

TEST(MatrixGeneratorTests, InvalidParameters){
    EXPECT_THROW((generateRandomMatrix<Matrix<int>>(0, -5, 5)), std::invalid_argument);
    EXPECT_THROW((generateRandomMatrix<Matrix<int>>(10, 5, -5)), std::invalid_argument);
}
