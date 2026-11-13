#include <gtest/gtest.h>
#include "matrix/Matrix.hpp"
#include "determinant/Gaussian.hpp"

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