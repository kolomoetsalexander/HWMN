#include <gtest/gtest.h>
#include <utility>
#include "matrix/JaggedMatrix.hpp"

TEST(JaggedMatrixTests, Constructor){
    JaggedMatrix<int> matrix(3, 4);

    EXPECT_EQ(matrix.rows(), 3);
    EXPECT_EQ(matrix.cols(), 4);
    EXPECT_EQ(matrix(0, 0), 0);
    EXPECT_EQ(matrix(2, 3), 0);
}
TEST(JaggedMatrixTests, ElementAccess){
    JaggedMatrix<int> matrix(2, 3);
    matrix(0, 0) = 10;
    matrix(1, 2) = 20;

    EXPECT_EQ(matrix(0, 0), 10);
    EXPECT_EQ(matrix(1, 2), 20);
    EXPECT_THROW(matrix(2, 0), std::out_of_range);
    EXPECT_THROW(matrix(0, 3), std::out_of_range);
}
TEST(JaggedMatrixTests, CopyConstructor){
    JaggedMatrix<int> a(2, 2);
    a(0, 0) = 10;
    a(1, 1) = 20;
    JaggedMatrix<int> b(a);

    EXPECT_EQ(b(0, 0), 10);
    EXPECT_EQ(b(1, 1), 20);
    b(0, 0) = 50;
    EXPECT_EQ(a(0, 0), 10);
    EXPECT_EQ(b(0, 0), 50);
}
TEST(JaggedMatrixTests, CopyAssignment){
    JaggedMatrix<int> a(2, 2);
    a(0, 0) = 10;
    JaggedMatrix<int> b(3, 3);
    b(0, 0) = 50;
    b = a;

    EXPECT_EQ(b.rows(), 2);
    EXPECT_EQ(b.cols(), 2);
    EXPECT_EQ(b(0, 0), 10);
    b(0, 0) = 100;
    EXPECT_EQ(a(0, 0), 10);
    EXPECT_EQ(b(0, 0), 100);
}
TEST(JaggedMatrixTests, MoveConstructor){
    JaggedMatrix<int> a(2, 2);
    a(0, 0) = 42;
    JaggedMatrix<int> b(std::move(a));

    EXPECT_EQ(b.rows(), 2);
    EXPECT_EQ(b.cols(), 2);
    EXPECT_EQ(b(0, 0), 42);
    EXPECT_EQ(a.rows(), 0);
    EXPECT_EQ(a.cols(), 0);
}
TEST(JaggedMatrixTests, MoveAssignment){
    JaggedMatrix<int> a(2, 2);
    a(0, 0) = 42;
    JaggedMatrix<int> b(3, 3);
    b = std::move(a);

    EXPECT_EQ(b.rows(), 2);
    EXPECT_EQ(b.cols(), 2);
    EXPECT_EQ(b(0, 0), 42);
    EXPECT_EQ(a.rows(), 0);
    EXPECT_EQ(a.cols(), 0);
}
TEST(JaggedMatrixTests, SelfAssignment){
    JaggedMatrix<int> a(2, 2);
    a(0, 0) = 42;
    a = a;

    EXPECT_EQ(a(0, 0), 42);
}

TEST(JaggedMatrixTests, SelfMoveAssignment){
    JaggedMatrix<int> a(2, 2);
    a(0, 0) = 42;
    a = std::move(a);

    EXPECT_EQ(a.rows(), 2);
    EXPECT_EQ(a.cols(), 2);
    EXPECT_EQ(a(0, 0), 42);
}
TEST(JaggedMatrixTests, ConstElementAccess){
    JaggedMatrix<int> a(2, 2);
    a(0, 0) = 42;
    const JaggedMatrix<int>& ref = a;

    EXPECT_EQ(ref(0, 0), 42);
    EXPECT_THROW(ref(2, 0), std::out_of_range);
}