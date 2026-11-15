#include <gtest/gtest.h>
#include "matrix/Matrix.hpp"
#include "matrix/JaggedMatrix.hpp"
#include "determinant/Gaussian.hpp"
#include "determinant/Bareiss.hpp"
#include "benchmarks/GenerateMatrices.hpp"

//gaussian contiguous storage
TEST(LargeMatrixTests, GaussianMatrix){
    constexpr size_t N = 1000;
    auto matrix = generateUpperTriangularMatrix<Matrix<double>>(N);
    auto original = matrix;

    EXPECT_NEAR(gaussian(matrix), 1.0, 1e-9);

    //the original value did not change after calculating the determinant
    for (size_t i = 0; i < N; ++i){
        for (size_t j = 0; j < N; ++j){
            EXPECT_DOUBLE_EQ(matrix(i, j), original(i, j));
        }
    }
}

//gaussian jagged storage
TEST(LargeMatrixTests, GaussianJaggedMatrix){
    constexpr size_t N = 1000;
    auto matrix = generateUpperTriangularMatrix<JaggedMatrix<double>>(N);

    EXPECT_NEAR(gaussian(matrix), 1.0, 1e-9);
}

//bareiss contiguous storage
TEST(LargeMatrixTests, BareissMatrix){
    constexpr size_t N = 1000;
    auto matrix = generateUpperTriangularMatrix<Matrix<long long>>(N);
    auto original = matrix;

    EXPECT_EQ(bareiss(matrix), 1);
    //as a test No.1
    for (size_t i = 0; i < N; ++i){
        for (size_t j = 0; j < N; ++j){
            EXPECT_EQ(matrix(i, j), original(i, j));
        }
    }
}

//bareiss jagged storage
TEST(LargeMatrixTests, BareissJaggedMatrix){
    constexpr size_t N = 1000;
    auto matrix = generateUpperTriangularMatrix<JaggedMatrix<long long>>(N);

    EXPECT_EQ(bareiss(matrix), 1);
}
