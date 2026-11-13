#include <gtest/gtest.h>
#include "matrix/Matrix.hpp"

TEST(MatrixTests, Constructor){
    Matrix<int> matrix(3, 4);

    EXPECT_EQ(matrix.rows(), 3);
    EXPECT_EQ(matrix.cols(), 4);
    EXPECT_EQ(matrix(0, 0), 0);
    EXPECT_EQ(matrix(2, 3), 0);
}
TEST(MatrixTests, ElementAccess){
    Matrix<int> matrix(2, 3);
    matrix(0, 0) = 10;
    matrix(1, 2) = 20;

    EXPECT_EQ(matrix(0, 0), 10);
    EXPECT_EQ(matrix(1, 2), 20);
    EXPECT_THROW(matrix(2, 0), std::out_of_range);
    EXPECT_THROW(matrix(0, 3), std::out_of_range);
}
TEST(MatrixTests, CopyConstructor){
    Matrix<int> a(2, 2);
    a(0, 0) = 10;
    Matrix<int> b(a);

    EXPECT_EQ(b(0, 0), 10);
    b(0, 0) = 50;
    EXPECT_EQ(a(0, 0), 10);
    EXPECT_EQ(b(0, 0), 50);
}
TEST(MatrixTests, MoveConstructor){
    Matrix<int> a(2, 2);
    a(0, 0) = 42;
    Matrix<int> b(std::move(a));

    EXPECT_EQ(b(0, 0), 42);
    EXPECT_EQ(a.rows(), 0);
    EXPECT_EQ(a.cols(), 0);
}
TEST(MatrixTests, CopyAssignment){
    Matrix<int> a(2, 2);
    a(0, 0) = 10;
    Matrix<int> b(3, 3);
    b(0, 0) = 50;
    b = a;

    EXPECT_EQ(b.rows(), 2);
    EXPECT_EQ(b.cols(), 2);
    EXPECT_EQ(b(0, 0), 10);
    b(0, 0) = 100;
    EXPECT_EQ(a(0, 0), 10);
    EXPECT_EQ(b(0, 0), 100);
}
TEST(MatrixTests, MoveAssignment){
    Matrix<int> a(2, 2);
    a(0, 0) = 42;
    Matrix<int> b(3, 3);
    b = std::move(a);

    EXPECT_EQ(b.rows(), 2);
    EXPECT_EQ(b.cols(), 2);
    EXPECT_EQ(b(0, 0), 42);
    EXPECT_EQ(a.rows(), 0);
    EXPECT_EQ(a.cols(), 0);
}
TEST(MatrixTests, SelfAssignment){
    Matrix<int> a(2, 2);
    a(0, 0) = 42;
    a = a;

    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a(0, 0), 42);
}
TEST(MatrixTests, SelfMoveAssignment){
    Matrix<int> a(2, 2);
    a(0, 0) = 42;
    a = std::move(a);

    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a(0, 0), 42);
}