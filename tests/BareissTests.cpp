#include <gtest/gtest.h>
#include "matrix/Matrix.hpp"
#include "determinant/Bareiss.hpp"

TEST(BareissTests, TwoByTwo){
    Matrix<long long> a(2, 2);
    a(0, 0) = 1;
    a(0, 1) = 2;
    a(1, 0) = 3;
    a(1, 1) = 4;
    EXPECT_EQ(bareiss(a), -2);
}

TEST(BareissTests, RowSwap){
    Matrix<long long> a(2, 2);
    a(0, 0) = 0;
    a(0, 1) = 2;
    a(1, 0) = 3;
    a(1, 1) = 4;

    EXPECT_EQ(bareiss(a), -6);
}

TEST(BareissTests, SingularMatrix){
    Matrix<long long> a(2, 2);
    a(0, 0) = 1;
    a(0, 1) = 2;
    a(1, 0) = 2;
    a(1, 1) = 4;

    EXPECT_EQ(bareiss(a), 0);
}
TEST(BarreissTests, ThreeByThree){
    Matrix<long long> a(3, 3);
    a(0, 0) = 2;
    a(0, 1) = 1;
    a(0, 2) = 3;
    a(1, 0) = 4;
    a(1, 1) = 5;
    a(1, 2) = 6;
    a(2, 0) = 7;
    a(2, 1) = 8;
    a(2, 2) = 9;

    EXPECT_EQ(bareiss(a), -9);
}
//when we creating an internal copy, the original matrix should not be modified (temp)
TEST(BareissTests, OriginalMatrixUnchanged){
    Matrix<long long> a(2, 2);
    a(0, 0) = 1;
    a(0, 1) = 2;
    a(1, 0) = 3;
    a(1, 1) = 4;

    bareiss(a);

    EXPECT_EQ(a(0, 0), 1);
    EXPECT_EQ(a(0, 1), 2);
    EXPECT_EQ(a(1, 0), 3);
    EXPECT_EQ(a(1, 1), 4);
}
TEST(BareissTests, OneByOne){
    Matrix<long long> a(1, 1);
    a(0, 0) = 7;

    EXPECT_EQ(bareiss(a), 7);
}
TEST(BareissTests, IdentityMatrix){
    Matrix<long long> a(3, 3);
    for (size_t i = 0; i < 3; ++i){
        a(i, i) = 1;
    }

    EXPECT_EQ(bareiss(a), 1);
}