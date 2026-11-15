#include "determinant/Determinant.hpp"
#include "determinant/Gaussian.hpp"
#include "determinant/Bareiss.hpp"

long long determinant(const Matrix<long long>& matrix){
    return bareiss(matrix);
}

long long determinant(const JaggedMatrix<long long>& matrix){
    return bareiss(matrix);
}

double determinant(const Matrix<double>& matrix){
    return gaussian(matrix);
}

double determinant(const JaggedMatrix<double>& matrix){
    return gaussian(matrix);
}